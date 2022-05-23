#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include "cardgame.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "blackjack.h"
#include "eCash.h"

using namespace std;

int main(){

    human Player(player::card_max);
    computer Computer(player::card_max);
    blackjack game;

    cout << endl;
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

    eCash eCash;
    eCash.login();
    eCash.query();

    int num_of_rounds;
    cout << endl;
    cout << "How many rounds you would like to play?" << endl;   
        while(!(cin >> num_of_rounds)){
                cout << "error: ";
                cin.clear();
                cin.ignore(123, '\n');
            } 
    cout << endl;

    game.blacjjack_welcome();
    cout << endl;

for (int round_num = 1; round_num <= num_of_rounds; round_num++) {
    eCash.change_bet();

        int count = 0; //number of cards have been drawn so far

        cout<<endl;
        cout<<endl;
        cout<<"###################  Round : "<< round_num << "  ######################"<<endl;
        
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
        Computer.choose_ace(count);

        //showing information to player
        Player.information_before_deciding_winner(Cactualcards, count);

    //computer may call the game at this point
    if (Computer.if_diff_10(Phandcard, count) == true){
        
        cout << "Dealer have chose to stay." << endl;
        cout << '\n';

            string prompt_2 = "Please enter 'decide' to decide winner of this round: ";
            string word_2 = "decide";
            game.trigger(prompt_2, word_2);
            cout << '\n';

        //writing in the value of the decider
        cout << "Your sum is: " << game.get_sum(Phandcard,count) << endl;

            display_index = 0;
            game.display_cards(display_index, Cactualcards, count);
            Computer.show_computer_cards(count);

            int decider = game.decide_winner(game.get_sum(Phandcard,count),game.get_sum(Chandcard,count));
            eCash.consume(decider);
                
            //writing in the score
            game.write_score(decider);

    } 
    
    if (Computer.if_diff_10(Phandcard, count) == false ) {
        
        //cout << '\n';
        cout << "Dealer have chose to hit." << endl;

        //check if sum == 21, hint is given if true
        Player.checkif_21_hint(count);

        //Change or switch another card or not, then rerun this process
        string more_card; //more_card as the trigger word
        more_card = Player.morecard_prompt(more_card);
        cout << '\n';

        //give more cards
        while (more_card == "hit"){
            //player cards
            Player.get_card(count);
            //computer cards
            Computer.get_card(count);
            count++;

            //check if sum == 21, hint is given if true
            Player.checkif_21_hint(count);

            display_index = 1;
            game.display_cards(display_index, Pactualcards, count);

            more_card = "stay";

            if (game.checkif_blow(Phandcard,count) == 0){
                more_card = Player.morecard_prompt(more_card);
                cout << '\n';
            } else if (game.checkif_blow(Phandcard,count) == 1){
                more_card = "stay";
            } else if(Computer.computer_checkif_over_18(count) == "no")
                more_card = "stay";
        }
    
        //computer try to gain advantages by switching Ace value
        Computer.choose_ace(count);

        Player.information_before_deciding_winner(Cactualcards ,count);

        //at this point player or dealer have called the round
        string prompt_3 = "Please enter 'decide' to decide winner of this round: ";
        string word_3 = "decide";
        game.trigger(prompt_3, word_3);
        cout << '\n';
        
        display_index = 0;
        game.display_cards(display_index, Cactualcards, count);
        Computer.show_computer_cards(count);

        int decider = game.decide_winner(game.get_sum(Phandcard,count),game.get_sum(Chandcard,count));

        eCash.consume(decider);
        if (eCash.get_money() == 0){
            cout << "Game will terminate." << endl;
            return 0;
        }

        game.write_score(decider);

    }
        game.refresh_card(Phandcard);
        game.refresh_card(Chandcard);

        if (round_num != num_of_rounds){
        //cout << "###################  ROUND BREAK  ###################" << endl;
        string prompt_4 = "Please enter 'next' to enter next round: ";
        string word_4 = "next";
        game.trigger(prompt_4, word_4);
        cout << '\n';
        }

}

    game.print_score();

    Player.~human();
    Computer.~computer();
    game.~blackjack();

    game.refresh_carddeck();
    return 0;
}