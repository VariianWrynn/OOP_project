#ifndef PLAYER_H
#define PLAYER_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class player{
    
    public:
    static const int card_max = 5;

    virtual void choose_ace(int count) = 0;

    virtual void get_card(int count) = 0;
};

#endif //PLAYER_H