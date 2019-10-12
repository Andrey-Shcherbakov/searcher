class akm{
    private:
        std:: string s;//искомый кусок
        std:: vector<int> pf;//префикс-функция
        
        void pff ();
        void AKM ();
    public:
        akm(std:: string&);
        std:: vector<std:: vector <int> > table;//автомат
};
           


