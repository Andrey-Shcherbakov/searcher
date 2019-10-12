#include <iostream>
#include <string>
#include <vector>
#include "akm.hpp"

akm:: akm(std:: string &pattern): pf (s.length(), 0), table(s.length(), std:: vector <int> (256, -1)){
    s = pattern;
    std:: cout << s << endl << pf.length();
    pff();
    AKM();
}

void akm:: AKM (){
    int len = s.length();

    std:: fill(table[0].begin(),table[0].end(),0);
    table[0][(int)(s[0])] = 1;


    for(int q = 1; q < len; q++){

        for(int a = 0; a < 256; a++){
            if(a == (int)(s[q])) table[q][a] = q + 1;
            else table[q][a] = table[pf[q]][a];
        }
    }
} 

void akm:: pff(){
    pf[0] = 0;
	for (int k = 0, i = 1; i < s.length(); ++i) 
	{
		while ((k > 0) && (s[i] != s[k]))
			k = pf[k-1];

		if (s[i] == s[k])
			k++;

		pf[i] = k;
	}
}

int main(){
    std:: string l = "abbac";
    akm A(l);
    std:: cout <<A.table[0][(int)('a')];
    return 0;
}
