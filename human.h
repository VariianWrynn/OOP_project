#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class human : public player
{   
    public:
    int* actual_cards;//this store cards that actually have been drawn by player
    int* cards;//this stores the value that will be proced by program
    //this is to allow program to process modified values, such as for black jack, J Q K are considered as has value of 10

    human();
    human(int size){ 
        cards = new int[size];
        actual_cards = new int [size];
    } 
    ~human(){
        delete actual_cards;
        delete cards;
    }

    int* get_cards_ptr(){return actual_cards;}  
    //This function must be called before comparison, check if any Ace was drawn, and switch on that Ace
    //Return value is the pointer points to the newly switched player's handcard

    /////////////////polymorphism//////////////
    void get_card(int count);
    //switch the value of any ace drawn
    void choose_ace(int count);


    void checkif_21_hint(int count);
    //this asks player if player wants any card and validate input
    string morecard_prompt(string more_card);
    
    //this will display sum of player's cards and dealer's first card. Also enable player to switch the value of any ace drawn
    void information_before_deciding_winner(int* computer_actualcards, int count);
};

#endif //HUMAN_H