#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "eCash.h"
#include "human.h"
#include "cardgame.h"
#include "blackjack.h"

using namespace std;

//#################### eCash CLASS IMPLENMENTATIONS####################//

eCash::eCash(){
    Money = 200;  //Basic balance for new customer
    file = fopen("eCash.txt", "r");
    fscanf(file, "%d", &Money);
    fclose(file);
    string ID[80];
}

int eCash::login(){
    string ID1 = "\0";
    cout << "Please enter your eCash ID: ";
    cin >> ID;
    cout << endl;

    if(ID != ID1){
        cout << "Login Success!" << endl;
        cout << endl;
        cout << "Hi " << ID << endl;
        return 0;
    }
    else{
        cout << "Login Errorr!" << endl;
        cout << "Good Bye." << endl;
        return 1;
    }
}

void eCash::logout(){
    exit(0);
}

//store = deposit
//Use the game points or money in eCash to exchange rewards or play more games.
void eCash::save( int Money1 ) {
    file = fopen("eCash.txt", "w+");
    fscanf(file, "%d", &Money);
    Money = Money + Money1;
    cout << "eCash: You deposit " << Money1 << " AUD" << endl;
    cout << "eCash: Balance: " << Money << " AUD" << endl;
    fprintf(file,"%d", Money);
    fclose(file);
}

int eCash::change_bet(){
        cout << "How much would like to bet for this round?" << endl;   
            int num;
                while(!(cin >> num) || num > Money)
                {
                    cout << "error: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                cout << "Your bet for this round is:  " << num << '.' << endl;
            bet = num;
            return 0;
        }

//Automactically charge ticket before player enter the game and add the "bet" function.
void eCash::consume(int decider){
    switch (decider) {
        case 1:
            file = fopen("eCash.txt", "w+");
            fscanf(file, "%d", &Money);
            Money += bet;  //Each game play once will cost $50.
            cout << "Your balance: " << Money << " AUD" << endl;
            fprintf(file, "%d", Money);
            fclose(file);
        break;
        
        case 0:
            cout << "Your balance: " << Money << " AUD" << endl;
        break;

        case -1:
            if( Money >= bet ) {
            file = fopen("eCash.txt", "w+");
            fscanf(file, "%d", &Money);
            Money -= 2*bet;  //Each game play once will cost $50.
            cout << "Your balance: " << Money << " AUD" << endl;
            fprintf(file, "%d", Money);
            fclose(file);
        break;
        }
    }
    if( Money < 0 ){
        cout << "eCash: Your balance is below zero. Current balance: " << Money - bet << " AUD" << endl;
    }
}

//display = query
void eCash::query(){
    file = fopen("eCash.txt", "r");
    fscanf(file,"%d", &Money);
    cout << "Your balance is: " << Money << " AUD" << endl;
    fclose(file);
}
