#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "human.h"
#include "cardgame.h"
#include "blackjack.h"

using namespace std;

//#################### HUMAN CLASS IMPLENMENTATIONS####################//

void human::get_card(int count){
    card_game A;

    //generate a number from 1 to 13
    int index = rand() % A.deck_size;
    //draw a card from the carddeck into handcard
    static const int prevent_redraw = 20;
    //if that card is already drawn (>20), a new index will be generated until it is not
    while (A.carddeck[index] > prevent_redraw){
        index = rand() % A.deck_size;
    }
    //+20 for any card that is drawn
    cards[count] = A.carddeck[index];
    actual_cards[count] = cards[count];
    
    if (cards[count] == 11 || cards[count] == 12 || cards[count] == 13){
        cards[count] = 10;
    }
    A.carddeck[index] = A.carddeck[index] + prevent_redraw;
}


void human::checkif_21_hint(int count){
    blackjack A;
    if (A.checkif_21(cards, count) == true){
            cout << "You have reached 21 point! Do not ask for any more cards!" << endl;
        }
return;
}

//This function must be called before comparison, check if any Ace was drawn, and switch on the Ace drawn
//Return value is the pointer points to the newly switched player's handcard
void human::choose_ace(int count){
    //check if the card drawn is Ace
    //int* ace_checked = new int [count];
    string prvent_crush;
    card_game Q;

    for (int i = 0; i < count; i++){
        if (cards[i] == 1){
            cout << "You have drawn an Ace!" << endl;
            cout << "What point would you like this Ace to be? (11 or 1)" << endl;
            
            cin >> prvent_crush;
                //making sure that player does not enter unexpected things
                while ( prvent_crush != "11" && prvent_crush != "1") {
                    cout << "Invalid input! Ace can only take 11 or 1, please enter again" << endl;
                    cin >> prvent_crush;

                    if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                    
                }

                if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }

                //making sure that the player does not simply switch to blow
                int sum = Q.get_sum(cards, count);
                if (sum > 21) {
                    cout << "By switching this Ace, you will have more than 21 points and lose this round (or draw), are you sure about that?" << endl;
                    cout << "Please enter the decided value of this Ace: ";

                    cin >> prvent_crush;
                //making sure that player does not enter unexpected things
                while ( prvent_crush != "11" && prvent_crush != "1") {
                    cout << "Invalid input! Ace can only take 11 or 1, please enter again" << endl;
                    cin >> prvent_crush;

                    if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                    
                }

                if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                }
        }
    }
    return;
}

string human::morecard_prompt(string more_card){
    cout << "Would you like to hit or stay?" << endl;
        cin >> more_card;
        while (more_card != "hit" && more_card != "stay"){
            cout << "Please enter 'hit' or 'stay' " << endl;
            cin >> more_card;
        }
    return more_card;
}

void human::information_before_deciding_winner(int* computer_actualcards, int count){

    blackjack game;
    //card_game game;
    //displaying the first card that computer have drawn
        cout <<"The fisrt card that dealer have drawn is: ";

        if (computer_actualcards[0] == 1){
            cout << "A" << endl;
        } else if (computer_actualcards[0] == 11){
            cout << "J" << endl;
        } else if (computer_actualcards[0] == 12){
            cout << "Q" << endl;
        } else if (computer_actualcards[0] == 13){
            cout << "K" << endl;
        } else {
            cout << computer_actualcards[0] << endl;
        }

        cout << "Your sum is: "<< game.get_sum(cards,count) << endl;
        cout << '\n';
        if (game.checkif_blow(cards,count) == 1){ 
                cout << "You have gone over 21 points" << endl;
            }

        //player switch on Ace
        if (game.checkif_blow(cards,count) == 0){
            if (game.checkif_Ace_exists(cards, count) == 1){
                choose_ace(count);
            }
        }
}


