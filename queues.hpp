#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <queue>
#include <string>
#include "akm.hpp"

//my queue for filenames
class drehen{
public:
    drehen (pthread_mutex_t&);
    void dpush(std:: string& );
    std::string dpop();
    bool empty;
    bool finished;
private:
    std::queue <std:: string > store;
    pthread_mutex_t &mut;
};

//my queue for result

struct Divedata{
    std::string adr;
    akm &A;
    drehen &D;
    pthread_mutex_t &print;
    bool depth;
};

struct Searchdata{
    akm &A;
    drehen &D;
    pthread_mutex_t &print;
};
