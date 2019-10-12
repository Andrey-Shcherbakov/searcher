class akm{
    private:
        const std:: string s;//искомый кусок
        std:: vector<int> pf;//префикс-функция
        
        void pff (); //подсчет префикс-функции
        void AKM (); //подсчет таблицы переходов
    public:
        akm(const std:: string&);
        std:: vector<std:: vector <int> > table;//автомат
};
           


