#include <iostream>

using namespace std;
int main(){
int bet = 0;
int money = 100;
        cout << "How much would like to bet for this round?" << endl;   
            int num;
                while(!(cin >> num) || num > money)
                {
                    cout << "error: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                cout << "Your bet for this round is: " << num << '.' << endl;
                bet = num;
}