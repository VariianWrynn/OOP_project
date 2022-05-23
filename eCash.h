#ifndef ECASH_H
#define ECASH_H

#include <iostream>
#include <string>

using namespace std;

class eCash
{   
    private:
        int Money;
        int bet;
        string ID;
        FILE *file;

    public:
        eCash();
        int get_money(){return Money;}
        int change_bet();
        int login();
        void logout(); 
        void save(int Money1);
        void consume(int decider);
        void query();
};

#endif //ECASH_H