#include <iostream>
#include <string>
#include <vector>

using namespace std;

int kmp(const char *needle, const int n_len, const char *stack){

    vector<int> pf (n_len); //префикс функция

	pf[0] = 0;
	for (int k = 0, i = 1; i < n_len; ++i) 
	{
		while ((k > 0) && (needle[i] != needle[k]))
			k = pf[k-1];

		if (needle[i] == needle[k])
			k++;

		pf[i] = k;
	}

	for (int k = 0, i = 0; needle[i] != '\0'; ++i) 
	{
		while ((k > 0) && (needle[k] != stack[i]))
			k = pf[k-1];

		if (needle[k] == stack[i])
			k++;

		if (k == n_len)
			return (i - n_len + 1); //либо продолжаем поиск следующих вхождений
	}

	return (string::npos);  
}
