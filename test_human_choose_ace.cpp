#include <iostream>
#include <numeric>
using namespace std;

int main(){

    string prvent_crush;

    const int count = 3;
    int cards[count] = {1,10,3};

    for (int i = 0; i < count; i++){
        if (cards[i] == 1){
            cout << "You have drawn an Ace!" << endl;
            cout << "What point would you like this Ace to be? (11 or 1)" << endl;
            
            cin >> prvent_crush;
                //making sure that player does not enter unexpected things
                while ( prvent_crush != "11" && prvent_crush != "1") {
                    cout << "Invalid input! Ace can only take 11 or 1, please enter again" << endl;
                    cin >> prvent_crush;

                    if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                    
                }

                if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }

                //making sure that the player does not simply switch to blow
                    int sum1 = 0;
                    sum1 = std::accumulate(cards, cards+count, sum1);
                    cout << "sum1 is: " << sum1 << endl;

                if (sum1 > 21) {
                    cout << "By choss this Ace, you will have more than 21 points and lose this round (or draw), are you sure about that?" << endl;
                    cout << "Please enter the decided value of this Ace: ";

                    cin >> prvent_crush;
                //making sure that player does not enter unexpected things
                while ( prvent_crush != "11" && prvent_crush != "1") {
                    cout << "Invalid input! Ace can only take 11 or 1, please enter again" << endl;
                    cin >> prvent_crush;

                    if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                    
                }

                if (prvent_crush == "11") {
                        cards[i] = 11;
                    } else if (prvent_crush == "1") {
                        cards[i] = 1;
                    }
                }

            int sum2 = 0;
            sum2 = std::accumulate(cards, cards+count, sum2);
            cout << "sum2 is: " << sum2 << endl;

        }
    }
    return 0;
}