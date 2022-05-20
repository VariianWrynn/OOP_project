#ifndef CARDGAME_H
#define CARDGAME_H

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

//objects for card game
class card_game
{   
    public:

    static const int deck_size = 52;
    int carddeck[deck_size] = {     1,2,3,4,5,6,7,8,9,10,11,12,13,
                                    1,2,3,4,5,6,7,8,9,10,11,12,13,
                                    1,2,3,4,5,6,7,8,9,10,11,12,13,
                                    1,2,3,4,5,6,7,8,9,10,11,12,13     };
    //this is the winner deciding function, this function should not be called
    //as each card game has its own rule when deciding who win
    virtual int decide_winner(){return 0;}

    void trigger(string promption, string word_looking_for);

    //draw a card, place the drawn card at handcard[count]
    //the original dynamic array will be changed straight away
    virtual void get_card(int* handcard, int count);

    //return the sum of handcard
    int get_sum(int* handcard, int count);

    //display each card drawn by the player
    void display_cards(bool display_index, int* handcard, int count);

    //countdown.....for fun
    void countdown(int interval);

    //refresh carddeck to original values
    void refresh_carddeck();
};

//class for calculate 24 game
class _calculate24
{
    public:

};

#endif //CARDGAME_H