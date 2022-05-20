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

#include "computer.h"
#include "cardgame.h"
#include "blackjack.h"

using namespace std;

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
void computer::choose_ace(int count)
{
    card_game Q;
    blackjack game;

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
    blackjack Q;
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