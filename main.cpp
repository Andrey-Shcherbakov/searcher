#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include "akm.hpp"
#include "kmp.hpp"

int main(){
    DIR *dir;
    struct  dirent *ent;

    char directory[256] = "C:\\Users\\sherb\\OneDrive\\Desktop\\IT\\Searcher";
    dir = opendir(directory);

    const std:: string l = "abbac";
    akm A(l);
    std:: vector <result> r;

    while ((ent = readdir(dir)) != nullptr) {
        if(ent->d_name[0] != '.') {
            std::string hel = (std::string) (directory) + (char) (92) + (std::string) (ent->d_name);
            const char *hl = hel.c_str();
            kmp(hl, A, r);
            //std::printf("%s\n", ent->d_name);
        }
    }

    for(int i = 0; i < r.size(); i++){
        std:: cout <<r[i].name << " " << r[i].line  << " " << r[i].zeile << std:: endl;
    }

    closedir(dir);
    return 0;
}