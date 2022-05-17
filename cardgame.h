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
    //*handcard must be dynamically allocated!!! for both computer's and player's

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
 
//objects for 21 point game
class _21point_game : public card_game
{   
    private:
    static const int size_scores = 3;
    //contains scores, scores[0] for player, scores[1] for player, scores[2] for player
    int* scores;

    public:
    _21point_game(){
        scores = new int[size_scores];
        for (int i = 0; i < size_scores; i++){
            scores[i] = 0;
        }
    }
    ~_21point_game(){
        delete scores;
    }

    
    void print_score(){
        cout << "-------------------Scores-------------------" << endl;
        cout << "Player: " << scores[0] << endl;
        cout << "Computer: " << scores[1] << endl;
        cout << "Draw: " << scores[2] << endl;

        if (scores[0] > scores[1]){
            cout << "You have won the game!" << endl;
        } else if (scores[0] = scores[1]){
            cout << "This game was a draw." << endl;
        } else if (scores[0] < scores[1]){
            cout << "You have lost the game." << endl;
        }
        return;
    }

    void write_score(int decider);

    void welcome();

    //return true for sum == 21, otherwise false
    bool checkif_21(int* handcard, int count);

    //refresh player's card, take in a pointer, change each value at that address to 0
    void refresh_card(int* handcard);

    //take in the sum of all player's cards, check if blow, return 1 for blow
    bool checkif_blow(int* handcard, int count);

    //take in the number of cards player have drawn, check if 5 cards were drawn
    //return 1 for true. (draw 5 cards without blowing automatically win)
    bool checkif_five(int count);

    //check if any Ace exists
    bool checkif_Ace_exists(int* handcard, int count);

    //take in sum of player's cards and computer's cards, return 1 for player wins, -1 for computer wins and 0 for draw
    int decide_winner(int player_sum, int computer_sum);
};

class players{
    
    public:
    static const int card_max = 5;

    virtual void switch_ace(int count) = 0;

    virtual void get_card(int count) = 0;
};

class human : public players
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

    void get_card(int count);
    //switch the value of any ace drawn
    void switch_ace(int count);

    void checkif_21_hint(int count);
    //this asks player if player wants any card and validate input
    string morecard_prompt(string more_card);
    
    //this will display sum of player's cards and dealer's first card. Also enable player to switch the value of any ace drawn
    void information_before_deciding_winner(int* computer_actualcards, int count);
};

//making the game harder... computer will try to call for comparison, if computer has advantages
class computer : public players
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

    void get_card(int count);

    int* get_cards_ptr(){return cards;}

    //if the diff. between player's first card and all computer's cards is more than 10, computer will call for comparison.
    bool if_diff_10(int* playercards, int count);

    string computer_checkif_over_18(int count);

    //Ace staff
    //computer will try to gain advantages by switching Ace' value
    void switch_ace(int count);

    void show_computer_cards(int count);
};

//class for calculate 24 game
class _calculate24
{
    public:

};

#endif //CARDGAME_H