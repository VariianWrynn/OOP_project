#include <iostream>
#include <string>
//#include "human.h"

using namespace std;

class eCash
{   
    private:
        int Money;
        string ID;
        FILE *file;

    public:
eCash(){
    Money = 250;  //Basic balance for new customer
    file = fopen("eCash.txt", "r");
    fscanf(file, "%d", &Money);
    fclose(file);
    string ID[80];
}

int login(){
    string ID1 = "\0";
    cout << "=== Welcome ===" << endl;
    cout << "Enter your eCash ID: ";
    cin >> ID;
    cout << endl;

    if(ID != ID1){
        cout << "Login Success!" << endl;
        cout << endl;
        cout << "Dear " << ID << " VIP customer" << endl;
        return 0;
    }
    else{
        cout << "Login Errorr!" << endl;
        cout << "Good Bye." << endl;
        return 1;
    }
}

void logout(){
    exit(0);
}

//store = deposit
//Use the game points or money in eCash to exchange rewards or play more games.
void save( int Money1 ) {
    file = fopen("eCash.txt", "w+");
    fscanf(file, "%d", &Money);
    Money = Money + Money1;
    cout << "eCash: You deposit " << Money1 << " AUD" << endl;
    cout << "eCash: Balance: " << Money << " AUD" << endl;
    fprintf(file,"%d", Money);
    fclose(file);
}

//Automactically charge ticket before player enter the game.
void consume(){
    cout << "eCash: Cost $50 for entry." << endl;
    if( Money >= 50 ) {
        file = fopen("eCash.txt", "w+");
        fscanf(file, "%d", &Money);
        Money = Money - 50;  //Each game play once will cost $50.
        fprintf(file, "%d", Money);
        fclose(file);
    }
    else {
        cout << "eCash: Your balance is not enough. Remaining: " << Money << " AUD" << endl;
    }
    cout << "Your balance: " << Money << " AUD" << endl;
}

//display = query
void query(){
    file = fopen("eCash.txt", "r");
    fscanf(file,"%d", &Money);
    cout << "eCash: Balance: " << Money << " AUD" << endl;
    fclose(file);
}
};




int main(){
    eCash eCash;
    char input = ' ';
    int Money1 = 0;  

    if( eCash.login() == 0 ) {
   
    do {
    	cout << "=================================\n";
    	cout << "Welcome, please choose option: " << endl;
        cout << endl;
        cout << "Enter 's': Deposit" << endl;
        cout << "Enter 'p': Play 'Blackjack - 21points'" << endl;
        cout << "Enter 'd': Query balance" << endl;
        cout << "Enter 'q': Exit" << endl;;
        cout << "=================================\n";
        cout << "> ";
        cin >> input;
        switch( input ) {
            case 's':
                cout << "eCash: Please enter the deposit amount: " << endl; 
                cin >> Money1;
                if(Money1<0){
                    cout<<"eCash: Must bigger than 0"<<endl;
                    system("pause");
                    break;
				}
                eCash.save(Money1);
                system("pause");
                break;
            case 'p':
                eCash.consume();
                system("pause");
                break;
            case 'd':
                eCash.query();
                system("pause");
                break;
            case 'q':
            	cout << "eCash: Account Exit, archived (saved)!" << endl;
            	cout << "Thank you, Bye~" << endl;
            	eCash.logout(); 
                break;
            default:
            	break;
        }
        system("cls");
    } while( input != 'q' && input != 'p' );
}

system("cls");
system("run.exe");

return 0;
}