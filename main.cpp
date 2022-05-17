#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include "cardgame.h"

using namespace std;

int main(){

    human Player(players::card_max);
    computer Computer(players::card_max);
    _21point_game game;

    game.trigger("Enter 'start' to start the game: ", "start");
    
    game.welcome();

    //seed rand
    srand(time(NULL));

    int* Phandcard = Player.cards;
    int* Chandcard = Computer.cards;

    int* Pactualcards = Player.actual_cards;
    int* Cactualcards = Computer.actual_cards;

    //1 for player 0 for dealer, so display_cards function can display the proper promotion
    bool display_index;

    static const int firstround_num_cards = 2;
    int num_of_rounds = 5;

for (int round_num = 1; round_num <= num_of_rounds; round_num++) {

        int count = 0; //number of cards have been drawn so far

        cout<<"-------------------Round : "<< round_num << "-------------------"<<endl;
        
        for(int b = 0; b < firstround_num_cards; b++){
            //player cards
            Player.get_card(count);
            //computer cards
            Computer.get_card(count);
            count++;
        }

        //display each card drawn by the player
        display_index = 1;
        game.display_cards(display_index, Pactualcards, count);
        
        //computer try to gain advantages by switching Ace value
        Computer.switch_ace(count);

        //showing information to player
        Player.information_before_deciding_winner(Cactualcards, count);

        cout << "Dealer is thinking...";
        game.countdown(3);

    //computer may call the game at this point
    if (Computer.if_diff_10(Phandcard, count) == true){
            
        cout << "Dealer have called for comparsion!" << endl;
        
            string prompt_2 = "Please enter 'decide' to decide winner of this round: ";
            string word_2 = "decide";
            game.trigger(prompt_2, word_2);

        //writing in the value of the decider
        cout << game.get_sum(Phandcard,count) << endl;

            display_index = 0;
            game.display_cards(display_index, Cactualcards, count);
            Computer.show_computer_cards(count);

            int decider = game.decide_winner(game.get_sum(Phandcard,count),game.get_sum(Chandcard,count));
                
            //writing in the score
            game.write_score(decider);

    } 
    
    if (Computer.if_diff_10(Phandcard, count) == false ) {
        
        cout << "Dealer have not called for comparison." << endl;

        //check if sum == 21, hint is given if true
        Player.checkif_21_hint(count);

        //Change or switch another card or not, then rerun this process
        string more_card; //more_card as the trigger word
        more_card = Player.morecard_prompt(more_card);

        //give more cards
        while (more_card == "yes"){
            //player cards
            Player.get_card(count);
            //computer cards
            Computer.get_card(count);
            count++;

            //check if sum == 21, hint is given if true
            Player.checkif_21_hint(count);

            display_index = 1;
            game.display_cards(display_index, Pactualcards, count);

            more_card = "no";

            if (game.checkif_blow(Phandcard,count) == 0){
                more_card = Player.morecard_prompt(more_card);
            } else if (game.checkif_blow(Phandcard,count) == 1){
                more_card = "no";
            } else if(Computer.computer_checkif_over_18(count) == "no")
                more_card = "no";
        }
    
        //computer try to gain advantages by switching Ace value
        Computer.switch_ace(count);

        Player.information_before_deciding_winner(Cactualcards ,count);

        //at this point player or dealer have called the round
        string prompt_3 = "Please enter 'decide' to decide winner of this round: ";
        string word_3 = "decide";
        game.trigger(prompt_3, word_3);
        
        display_index = 0;
        game.display_cards(display_index, Cactualcards, count);
        Computer.show_computer_cards(count);

        int decider = game.decide_winner(game.get_sum(Phandcard,count),game.get_sum(Chandcard,count));

        game.write_score(decider);

    }
        game.refresh_card(Phandcard);
        game.refresh_card(Chandcard);

        if (round_num != 5){
        cout << "-------------------round break-------------------" << endl;
        string prompt_4 = "Please enter 'next' to enter next round: ";
        string word_4 = "next";
        game.trigger(prompt_4, word_4);
        }
}

    game.print_score();

    Player.~human();
    Computer.~computer();
    game.~_21point_game();

    game.refresh_carddeck();
    return 0;
}