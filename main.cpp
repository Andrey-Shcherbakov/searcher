#include <dirent.h>
#include <fstream>
#include <iostream>
#include "akm.hpp"
#include "parcer.hpp"
#include "queues.hpp"

int kmp(std::string filename, akm &A, pthread_mutex_t &print){
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
            }
            else {
                q = A.step(q, zeile[i]);
            }
        }
        line++;
    }
    f.close();
    return 0;
}

void Deep(std::string directory, drehen &D){
    DIR *dir;
    dir = opendir(directory.c_str());
    if (dir == NULL) {
        std::cout <<"here " << directory << "\n";
        perror("opendir");
        return;
    }
    for (auto ent = readdir(dir); ent != NULL; ent = readdir(dir)){
        std::string en = (std::string) (ent->d_name);
        if (en != "." && en != "..") {
            std::string hel = directory + (char)(47) + en;
		    if(ent->d_type == DT_REG) D.dpush(hel);
            if(ent->d_type == DT_DIR) Deep(hel, D);
		}
    }
    closedir(dir);
}

void *Dive (void *args){
    Divedata *a = (Divedata *)args;
    if(!(a->depth)){
        DIR *dir;
        dir = opendir(a->adr.c_str());
        if (dir == NULL) {
            std::cout <<"here " << a->adr << "\n";
            perror("opendir");
            return nullptr;
        }
        for (auto ent = readdir(dir); ent != NULL; ent = readdir(dir)){
            std::string en = (std::string) (ent->d_name);
            if (en != "." && en != "..") {
                std::string hel = a->adr + (char)(47) + en;
                if(ent->d_type == DT_REG) (a->D).dpush(hel);
            }
        }
        closedir(dir);
    }
    else {
        Deep(a->adr, a->D);
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

    //std:: cout << P.dir;

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
