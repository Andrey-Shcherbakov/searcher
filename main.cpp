#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include "akm.hpp"
#include "kmp.hpp"

void ODS(std::string directory, akm &A, std:: vector <result> &r){
    DIR *dir;
    struct  dirent *ent;
    dir = opendir(directory.c_str());

    //std::cout << directory <<" opened \n";

    while ((ent = readdir(dir)) != nullptr) {
        if(ent->d_name[0] != '.') {
            std::string hel = (directory) + (char) (92) + (std::string) (ent->d_name);
            const char *hl = hel.c_str();
            kmp(hl, A, r);
            //std::printf("%s\n", ent->d_name);
        }
        else{
            std::string en = (std::string) (ent->d_name);
            //std::cout << en << std::endl;
            if (en != "." && en != "..") {
                en.erase(en.begin());
                std::string hel = (directory) + (char) (92) + en;
                ODS(hel, A, r);
            }
        }
    }

    closedir(dir);
    //std::cout << directory <<" closed \n";
};

int main(){
    std::string directory = "C:\\Users\\sherb\\OneDrive\\Desktop\\IT\\Searcher";

    const std:: string l = "abbac";
    akm A(l);
    std:: vector <result> r;

    /*DIR *dir;
    struct  dirent *ent;
    dir = opendir(directory.c_str());

    while ((ent = readdir(dir)) != nullptr) {
        std::cout<< ent->d_name << "\n";
    }*/

    ODS(directory, A, r);

    for(int i = 0; i < r.size(); i++){
        std:: cout << r[i].name << " " << r[i].line  << " " << r[i].zeile << std:: endl;
    }
    return 0;
}