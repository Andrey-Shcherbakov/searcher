#include "akm.hpp"
#include <assert.h>

akm:: akm(const std:: string &pattern):s (pattern),
                                       pf (pattern.length(), 0),
                                       table(pattern.length(),std:: vector <int> (256, 0)){
    gotcha = s.length();
    pff();
    AKM();
}

int akm:: step(int q, char input) {
    assert((int)((unsigned char) input) < 256 && (int)((unsigned char) input) > 0);
    assert(q > 0 && q <= s.length());
    return table[q][(int)((unsigned char) input)];
}

void akm:: AKM (){
    int len = s.length();

    std:: fill(table[0].begin(),table[0].end(),0);
    table[0][(int)(s[0])] = 1;

    for(int q = 1; q < len; q++){
        for(int a = 0; a < 256; a++){ //may appear problems with range
            if(a == (int)((unsigned char)s[q])) table[q][a] = q + 1;
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

		assert(k < s.length() && k > 0);
		pf[i] = k;
	}
}