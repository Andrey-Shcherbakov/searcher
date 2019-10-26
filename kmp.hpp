#pragma once
#include <string>
#include <vector>
#include "akm.hpp"

struct result{
    std::string name;
    int line;
    std::string zeile;
};

int kmp(const char *filename, akm &A, std:: vector <result> &r);
