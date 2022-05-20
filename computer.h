#include <string>
#include "player.h"

using namespace std;

#ifndef COMPUTER_H
#define COMPUTER_H

//making the game harder... computer will try to call for comparison, if computer has advantages
class computer : public player
{
    public:
    int* actual_cards;//this store cards that actually have been drawn by player
    int* cards;//this stores the value that will be proced by program
    //this is to allow program to process modified values, such as for black jack, J Q K are considered as has value of 10

    computer();
    computer(int size){ 
        cards = new int [size];
        actual_cards = new int [size];
    }
    ~computer(){
        delete actual_cards;
        delete cards;
    }
   
    //Ace staff
    //computer will try to gain advantages by switching Ace' value
    void choose_ace(int count);
    void get_card(int count);

    int* get_cards_ptr(){return cards;}

    //if the diff. between player's first card and all computer's cards is more than 10, computer will call for comparison.
    bool if_diff_10(int* playercards, int count);

    string computer_checkif_over_18(int count);

    void show_computer_cards(int count);
};
#endif //COMPUTER_H