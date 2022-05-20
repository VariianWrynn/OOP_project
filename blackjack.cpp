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

#include "blackjack.h"

using namespace std;

//#################### _21POINT_GAME CLASS IMPLENMENTATIONS####################//

void blackjack::write_score(int decider){
            if ( decider == 1 ){
                scores[0]++;
            } else if ( decider == -1){
                scores[1]++;
            } else if ( decider == 0){
                scores[2]++;
            }
    return;
}

void blackjack::welcome(){
    card_game game;

    cout << "This is a simple balck jack game (Twenty-one game), you will be playing as a player against dealer which controlled by computer." << endl;
    cout << "For rules, please go to: https://en.wikipedia.org/wiki/Blackjack" << endl;
    cout << "----------------------------------------------------------------" << endl;

    string prvent_crush;
    cout << "Enter 'start' to start the game: ";
    cin >> prvent_crush;
    while (prvent_crush != "start")
    {
        cout << "Enter 'start' to start the game: ";
        cin >> prvent_crush;
    }

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

void blackjack::refresh_card(int* handcard){
    for (int i = 0; i < 5; i++){
    handcard[i] = 0;
    }
}

//return 1 for blow
bool blackjack::checkif_blow(int* handcard, int count){
    card_game A;
    int sum = A.get_sum(handcard, count);
    if (sum > 21){
        return 1;
    }
return 0;
}

//check if five, return 1 for five cards have been drawn
bool blackjack::checkif_five(int count){
    if (count >= 4){
        return 1;
    }
return 0;
}

bool blackjack::checkif_21(int* handcard, int count){
    card_game A;
        if (A.get_sum(handcard,count) == 21){
            return true;
        }
return false;
}

//check if any Ace exists
//return 1 for yes
bool blackjack::checkif_Ace_exists(int* handcard, int count){
    for (int i = 0; i < count; i++){
        if (handcard[i] == 1){
            return 1;
        }
    }
    return 0;
}

//winner deciding function, this is triggered when comparison is called
//return 1 for player wins, -1 for computer wins and 0 for draw
int blackjack::decide_winner(int player_sum, int computer_sum){
    //when both player and computer is under 21 point
    if (player_sum <= 21 && computer_sum <= 21){
        if (player_sum > computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "You have won this round!" << endl;
            cout << "----------------------------------------------" << endl;
            return 1;
        } else if (player_sum == computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "This round was a draw"<< endl;
            cout << "----------------------------------------------" << endl;
            return 0;
        } else if (player_sum < computer_sum){
            cout << "----------------------------------------------" << endl;
            cout << "You have lost this round"<< endl;
            cout << "----------------------------------------------" << endl;
            return -1;
        }
    }

    //when player blow (over 21 point), and computer is blow 21
    if (player_sum > 21 && computer_sum <= 21){
        cout << "----------------------------------------------" << endl;
            cout << "You have lost this round"<< endl;
            cout << "----------------------------------------------" << endl;
            return -1;
    }
    //when computer blow and player under 21
    if (player_sum <= 21 && computer_sum > 21){
        cout << "----------------------------------------------" << endl;
            cout << "You have won this round"<< endl;
            cout << "----------------------------------------------" << endl;
            return 1;
    }
    //when both blow
    if (player_sum > 21 && computer_sum > 21){
        cout << "----------------------------------------------" << endl;
            cout << "This round was a draw"<< endl;
            cout << "----------------------------------------------" << endl;
            return 0;
        }
    return 0;
    }

    void blackjack::print_score(){
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