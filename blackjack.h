#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "cardgame.h"

//objects for blcakjack game
class blackjack : public card_game
{   
    private:
    static const int size_scores = 3;
    //contains scores, scores[0] for player, scores[1] for player, scores[2] for player
    int* scores;

    public:
    blackjack(){
        scores = new int[size_scores];
        for (int i = 0; i < size_scores; i++){
            scores[i] = 0;
        }
    }
    ~blackjack(){
        delete scores;
    }
    
    void print_score();

    void write_score(int decider);

    void welcome();

    void blacjjack_welcome();

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

#endif //BLACKJACK_H
