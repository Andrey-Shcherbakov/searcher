#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "akm.hpp"
#include "kmp.hpp"

int kmp(const char *filename, akm &A, std:: vector <result> &r){
    //std::cout << filename << std::endl;
    std::ifstream f;
    f.open(filename);

    std::string zeile;
    int line = 1, q = 0;
    result res;
    res.name = filename;
    while(std::getline(f, zeile)){
        //std:: cout << line  << zeile << std::endl;
        for(int i = 0;  i < zeile.length(); i++){
            if (q == A.gotcha) {
                res.line = line;
                res.zeile = zeile;
                r.push_back(res);
                q=0;
                break;
            } else {
                q = A.step(q, zeile[i]);
            }
            //std:: cout << q << " " << (int)zeile[i] << std:: endl;
        }
        line++;
    }
    f.close();
    return 0;
}

/*int main(){
    const std:: string l = "abbac";
    const char title[62] = "C:\\Users\\sherb\\OneDrive\\Desktop\\IT\\Searcher\\akm.hpp";
    akm A(l);
    std:: vector <result> r;
    kmp(title, A, r);
    for(int i = 0; i < r.size(); i++){
        std:: cout << r[i].line  << " " << r[i].zeile << std:: endl;
    }
    return 0;
}*/