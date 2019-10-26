#pragma once
#include <iostream>
#include <string>
#include <vector>
class akm{
    private:
        const std:: string s;
        std:: vector<int> pf;
        std:: vector<std:: vector <int> > table;

        void pff ();
        void AKM ();
    public:
        akm(const std:: string&);
        int gotcha;
        int step(int , char);
};