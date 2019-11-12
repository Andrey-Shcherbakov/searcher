#pragma once
#include <iostream>
#include <string>
class parcer{
public:
    parcer(int argc, char *argv[]);
    int tN;
    std::string l; //pattern
    bool depth;
    std::string dir;
};
