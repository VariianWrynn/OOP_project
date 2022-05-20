#include <string>
#include <time.h>
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

void card_game::trigger(string promption, string word_looking_for){
    string prvent_crush;
    cout << promption;
    cin >> prvent_crush;
    while (prvent_crush != word_looking_for)
    {
        cout << promption;
        cin >> prvent_crush;
    }
    return;
}

//draw a new card, *handcard must be dynamically allocated
void card_game::get_card(int* handcard, int count){

    //generate a number from 0 to 51
    int index = rand() % deck_size;
    //draw a card from the carddeck into handcard
    static const int prevent_redraw = 20;
    //if that card is already drawn (>20), a new index will be generated until it is not
    while (carddeck[index] > prevent_redraw){
        index = rand() % deck_size;
    }
    //+20 for any card that is drawn
    handcard[count] = carddeck[index];
    carddeck[index] = carddeck[index] + prevent_redraw;
}

//caluate sum
int card_game::get_sum(int* handcard, int count){
    int sum = 0;
    for (int i = 0; i < count; i++){
        sum += handcard[i];
    }
    return sum;
}

//display all cards
void card_game::display_cards(bool display_index, int* handcard, int count){

    //Another object can print or display the state of an object on the screen
    
    if (display_index == 1){
        cout << "Cards you have drawn are: ";
    } else if (display_index == 0){
        cout << "Cards dealer have drawn are: ";
    }

    string actual_cards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < count; i++){
        switch (handcard[i]){
            case 1:
            cout << actual_cards[0] << ' ';
            break;
            case 2:
            cout << actual_cards[1] << ' ';
            break;
            case 3:
            cout << actual_cards[2] << ' ';
            break;
            case 4:
            cout << actual_cards[3] << ' ';
            break;
            case 5:
            cout << actual_cards[4] << ' ';
            break;
            case 6:
            cout << actual_cards[5] << ' ';
            break;
            case 7:
            cout << actual_cards[6] << ' ';
            break;
            case 8:
            cout << actual_cards[7] << ' ';
            break;
            case 9:
            cout << actual_cards[8] << ' ';
            break;
            case 10:
            cout << actual_cards[9] << ' ';
            break;
            case 11:
            cout << actual_cards[10] << ' ';
            break;
            case 12:
            cout << actual_cards[11] << ' ';
            break;
            case 13:
            cout << actual_cards[12] << ' ';
            break;
        }
    }
    cout << '\n';
}

//countdown from intercval to 1
void card_game::countdown(int interval){
    for (int i = 0; i < interval; i++){
        std::cout << interval-i << ' ';
        Sleep(1000);
        if (i == interval-1){
            std::cout << '\n';
        }
    }
}

//refresh carddeck to original values
void card_game::refresh_carddeck(){
    card_game B;
    for (int i = 0; i < deck_size; i++){
        if (B.carddeck[i] > 20){
            B.carddeck[i] = B.carddeck[i] - 20;
        }
    }
}
