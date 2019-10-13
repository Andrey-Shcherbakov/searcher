#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "akm.hpp"
struct result{
    const char *name; //имя файла
    int line; //номер строки
    std::string zeile; //строка
};

int kmp(const char *filename, akm &A, std:: vector <result> &r){
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
        }
        line++;
    }
    f.close();
    return 0;
}

int main(){
    const std:: string l = "abbac";
    const char title[62] = "C:\\Users\\sherb\\OneDrive\\Desktop\\IT\\Searcher\\example.txt";
    akm A(l);
    std:: vector <result> r;
    kmp(title, A, r);
    for(int i = 0; i < r.size(); i++){
        std:: cout << r[i].line  << " " << r[i].zeile << std:: endl;
    }
    return 0;
}