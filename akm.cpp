#pragma once
#include "akm.hpp"

akm:: akm(const std:: string &pattern):s (pattern),
                                       pf (pattern.length(), 0),
                                       table(pattern.length(),std:: vector <int> (256, 0)){
    gotcha = s.length();
    pff();
    AKM();
}

int akm:: step(int q, char input) {
    return table[q][(int) input];
}

void akm:: AKM (){
    int len = s.length();

    std:: fill(table[0].begin(),table[0].end(),0);
    table[0][(int)(s[0])] = 1;

    for(int q = 1; q < len; q++){
        for(int a = 0; a < 256; a++){
            if(a == (int)(s[q])) table[q][a] = q + 1;
            else table[q][a] = table[pf[q-1]][a];
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
	//for(int i = 0; i < pf.size(); i++) std:: cout << pf[i] << " ";
}

/*int main(){
    const std:: string l = "abbac";
    akm A(l);
    std:: cout <<" automat table " << std:: endl;
    for(int j = (int)('a'); j < (int)('z'); j++) std::cout << (char)(j) << " ";
    std::cout<< std::endl;
    for(int i = 0; i < A.table.size(); i++){
        for(int j = (int)('a'); j < (int)('z'); j++){
            std::cout << A.table[i][j] << " ";
        }
        std:: cout << std:: endl;
    }
    return 0;
}*/
