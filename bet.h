#ifndef BET_H
#define BET_H

#include <string>
#include <human.h>

using namespace std;
//objects for blcakjack game
class Bet : public human
{   
    private:
    int money;
    int bet;
    FILE *file;

    public:
    Bet(){
        money = 250;  //Basic balance for new customer
        file = fopen("Bet_record.txt", "r");
        fscanf(file, "%d", &money);
        fclose(file);
    }
    Bet(int inital_money){
        file = fopen("Bet_record.txt", "w+");
        fscanf(file, "%d", &money);
         
        fprintf(file,"%d", money);
        fclose(file);
    }

    void bet_promption(){
        cout << "How much would like to bet for this round?" << endl;   
            int num;
                while(!(cin >> num) || num > money)
                {
                    cout << "error: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                cout << "Your bet for this round is:  " << num << '.' << endl;
                bet = num;
    }
    
    int get_money(){return money;}

    void change_money(int change){
        file = fopen("eCash.txt", "w+");
        fscanf(file, "%d", &money);
        money += change;
    
        fprintf(file,"%d", money);
        fclose(file);
    }
};

#endif //BET_H