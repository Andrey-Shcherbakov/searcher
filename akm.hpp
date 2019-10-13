#include <iostream>
#include <string>
#include <vector>
class akm{
    private:
        const std:: string s;//искомый кусок
        std:: vector<int> pf;//префикс-функция
        std:: vector<std:: vector <int> > table;//автомат

        void pff (); //подсчет префикс-функции
        void AKM (); //подсчет таблицы переходов
    public:
        akm(const std:: string&);
        int gotcha;
        int step(int , char); // получение следующего состояния из текущего по пришедшему символу
};
           


