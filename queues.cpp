#include "queues.hpp"

drehen:: drehen(pthread_mutex_t &mt): mut (mt){
    empty = true;
    finished = false;
}

void drehen::dpush(std::string &fname){
    pthread_mutex_lock(&mut);
    store.push(fname);
    //std:: cout << store.back() << std::endl;
    empty = false;
    pthread_mutex_unlock(&mut);
}

std::string drehen::dpop() {
    std::string s;
    pthread_mutex_lock(&mut);
    if(store.empty()) s = "";
    else{
        s = store.front();
        store.pop();
    }
    empty = store.empty();
    pthread_mutex_unlock(&mut);
    return s;
}