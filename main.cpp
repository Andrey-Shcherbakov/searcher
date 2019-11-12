#include <dirent.h>
#include <fstream>
#include <iostream>
#include "akm.hpp"
#include "parcer.hpp"
#include "queues.hpp"

int kmp(std::string filename, akm &A, pthread_mutex_t &print){
    //std::cout << filename << std::endl;
    std::ifstream f;
    f.open(filename.c_str());

    std::string zeile;
    int line = 1, q = 0;
    while(std::getline(f, zeile)){

        for(int i = 0;  i < zeile.length(); i++){
            if (q == A.gotcha) {
                pthread_mutex_lock(&print);
                std:: cout << filename << " " << line << " " << zeile << std::endl;
                pthread_mutex_unlock(&print);
                q=0;
                break;
            } else {
                q = A.step(q, zeile[i]);
            }
        }
        line++;
    }
    f.close();
    return 0;
}

void *Dive (void *args){
    Divedata *a = (Divedata *)args;
    DIR *dir;
    struct  dirent *ent;
    //std:: cout << &(a->D) << " \n";
    if(!(a->depth)){
        dir = opendir((a->adr).c_str());
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_name[0] != '.') {
                std::string hel = (a->adr) + (char) (92) +
                                  (std::string)(ent->d_name);//needs changing in linux on 47, windows - 92
                (a->D).dpush(hel);
            }
        }
        closedir(dir);
    }
    else {
        std::queue<std::string> dirs;
        dirs.push(a->adr);
        while (!(dirs.empty())) {
            std::string fn = dirs.front();
            dir = opendir((dirs.front()).c_str());
            dirs.pop();
            while ((ent = readdir(dir)) != nullptr) {
                if (ent->d_name[0] != '.') {
                    std::string hel = (fn) + (char) (92) +
                                      (std::string) (ent->d_name);//needs changing in linux on 47, windows - 92
                    //std::cout << hel << " may\n";
                    (a->D).dpush(hel);

                } else {
                    std::string en = (std::string) (ent->d_name);
                    if (en != "." && en != "..") {
                        en.erase(en.begin());
                        std::string hel = (fn) + (char) (92) + en;
                        //std:: cout  << hel <<" lost dirs\n";
                        dirs.push(hel);
                    }
                }
            }
            closedir(dir);
        }
    }
    (a->D).finished = true;
    while(!(a->D).empty){
        std::string s = (a->D).dpop();
        if (s != "") kmp(s, a->A, a->print);
    }
    return nullptr;
}

void *Search(void * args){
    //std:: cout << "mya";
    Searchdata *a = (Searchdata *)args;
    for(;;){
        while ((a->D).empty && !(a->D).finished);

        if ((a->D).finished){
            while(!(a->D).empty){
                std::string s = (a->D).dpop();
                //std:: cout << s << "\n";
                if (s != "") kmp(s, a->A, a->print);
            }
            return nullptr;
        }
        std::string s = (a->D).dpop();
        //std:: cout << s << "\n";
        if (s != "") kmp(s, a->A, a->print);
    }
}

int main(int argc, char *argv[]){
    parcer P(argc, argv);
    akm A(P.l);

    //std:: cout << P.depth;

    std::vector <pthread_t> thr(P.tN);
    pthread_mutex_t mut;
    pthread_mutex_t print;
    pthread_mutex_init(&mut, nullptr);
    pthread_mutex_init(&print, nullptr);

    drehen D(mut);

    Divedata d1 = {P.dir,A, D, print, P.depth};
    Searchdata d2 = {A, D, print};

    //std:: cout << P.dir << " dir\n";

    pthread_create(&thr[0], nullptr, Dive, &d1);
    for(int i = 1; i < P.tN; i++){
        pthread_create(&thr[i], nullptr, Search, &d2);
    }
    for(int i = 0; i < P.tN; i++){
        pthread_join(thr[i], nullptr);
    }
    return 0;
}