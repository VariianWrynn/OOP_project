#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "cardgame.h"

using namespace std;

//#################### _21POINT_GAME CLASS IMPLENMENTATIONS####################//

void _21point_game::write_score(int decider){
            if ( decider == 1 ){
                scores[0]++;
            } else if ( decider == -1){
                scores[1]++;
            } else if ( decider == 0){
                scores[2]++;
            }
    return;
}

void _21point_game::welcome(){
    card_game game;

    cout << "This is a simple balck jack game (Twenty-one game), you will be playing as a player against dealer which controlled by computer." << endl;
    cout << "For rules, please go to: https://en.wikipedia.org/wiki/Blackjack" << endl;
    cout << "-----------------------------------------------" << endl;

    srand(time(NULL));
    static const int nums_rands = 3;
    int rand_start = rand() % nums_rands;
    string start_prompt[nums_rands] = {"Bribing the dealer...", "Making AI harder...", "Shuffling cards..."};
    cout << start_prompt[rand_start] << endl;
    game.countdown(3);
    string word = "Start!";
    cout << word << endl;
    Sleep(500);

}

void _21point_game::refresh_card(int* handcard){
    for (int i = 0; i < 5; i++){
    handcard[i] = 0;
    }
}

//return 1 for blow
bool _21point_game::checkif_blow(int* handcard, int count){
    card_game A;
    int sum = A.get_sum(handcard, count);
    if (sum > 21){
        return 1;
    }
return 0;
}

//check if five, return 1 for five cards have been drawn
bool _21point_game::checkif_five(int count){
    if (count >= 4){
        return 1;
    }
return 0;
}

bool _21point_game::checkif_21(int* handcard, int count){
    card_game A;
        if (A.get_sum(handcard,count) == 21){
            return true;
        }
return false;
}

//check if any Ace exists
//return 1 for yes
bool _21point_game::checkif_Ace_exists(int* handcard, int count){
    for (int i = 0; i < count; i++){
        if (handcard[i] == 1){
            return 1;
        }
    }
    return 0;
}

//winner deciding function, this is triggered when comparison is called
//return 1 for player wins, -1 for computer wins and 0 for draw
int _21point_game::decide_winner(int player_sum, int computer_sum){
    //when both player and computer is under 21 point
    if (player_sum <= 21 && computer_sum <= 21){
        if (player_sum > computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "You have won this round!" << endl;
            return 1;
        } else if (player_sum == computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "This round was a draw"<< endl;
            return 0;
        } else if (player_sum < computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "You have lost this round"<< endl;
            return -1;
        }
    }

    //when player blow (over 21 point), and computer is blow 21
    if (player_sum > 21 && computer_sum <= 21){
        cout << "----------------------------------------------" << endl;
            cout << "You have lost this round"<< endl;
            return -1;
    }
    //when computer blow and player under 21
    if (player_sum <= 21 && computer_sum > 21){
        cout << "----------------------------------------------" << endl;
            cout << "You have won this round"<< endl;
            return 1;
    }
    //when both blow
    if (player_sum > 21 && computer_sum > 21){
        cout << "----------------------------------------------" << endl;
            cout << "This round was a draw"<< endl;
            return 0;
        }
    return 0;
    }


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
    _21point_game A;
    if (A.checkif_21(cards, count) == true){
            cout << "You have reached 21 point! Do not ask for any more cards!" << endl;
        }
return;
}

//This function must be called before comparison, check if any Ace was drawn, and switch on the Ace drawn
//Return value is the pointer points to the newly switched player's handcard
void human::switch_ace(int count){
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
    cout << "Would you like another card? (yes/no)" << endl;
        cin >> more_card;
        while (more_card != "yes" && more_card != "no"){
            cout << "Please enter 'yes' or 'no' " << endl;
            cin >> more_card;
        }
    return more_card;
}

void human::information_before_deciding_winner(int* computer_actualcards, int count){

    _21point_game game;
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
        if (game.checkif_blow(cards,count) == 1){ 
                cout << "You have gone over 21 points" << endl;
            }

        //player switch on Ace
        if (game.checkif_blow(cards,count) == 0){
            if (game.checkif_Ace_exists(cards, count) == 1){
                switch_ace(count);
            }
        }
}


//#################### COMPUTER CLASS IMPLENMENTATIONS####################//


void computer::get_card(int count){
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

//if the diff. between player's first card and all computer's cards is more than 10, computer will call for comparison.
//return 1 for calling comparison
bool computer::if_diff_10(int* playercards, int count){
    card_game Q;
    int sum = Q.get_sum(cards, count);
    if ( (sum-playercards[0]) > 10 || sum >= 20){
        return 1;
    }
    return 0;
}

//if (sum <= playercards[0] || sum <= 10) then switch to 11
void computer::switch_ace(int count)
{
    card_game Q;
    _21point_game game;

    int sum = Q.get_sum(cards, count);
    if ( sum <= 11 )
    {
        for ( int i = 0; i < count; i++ )
        {
            if ( cards[i] == 1 )
            {
                cards[i] = 11;
            }
        }
    }

    bool index = game.checkif_blow(cards, count);
    if ( index == 1 )
    {
        for ( int i = 0; i < count; i++ )
        {
            if ( cards[i] == 11 )
            {
                cards[i] = 1;
                return; //even though there might be multiple Ace, only one of them should be switched
            }
        }
    }
    return;
}

//return "no" if somputer's sum >= 18, thus prventing computer from excedding 21
string computer::computer_checkif_over_18(int count){
    _21point_game Q;
    if (Q.get_sum(cards, count) >= 18){
        cout << "Dealer have called for comparsion!" << endl;
        return "no";
    }
    return "yes";
}

void computer::show_computer_cards(int count){
    card_game game;
    cout << "Dealer's sum is: ";
        cout << game.get_sum(cards,count) << endl;
}