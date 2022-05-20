#include <iostream>
#include <numeric>
using namespace std;
//if (sum <= playercards[0] || sum <= 10) then switch to 11
int main()
{
    const int count = 2;
    int cards[count] = {1,10};

    int sum1 = 0;
    sum1 = std::accumulate(cards, cards+count, sum1);
    cout << "sum1 is: " << sum1 << endl;

    if ( sum1 <= 11 )
    {
        for ( int i = 0; i < count; i++ )
        {
            if ( cards[i] == 1 )
            {
                cards[i] = 11;
                cout << "switched to 11!" << endl;
            }
        }
    }

    int sum2 = 0;
    sum2 = std::accumulate(cards, cards+count, sum2);
    cout << "sum2 is: " << sum2 << endl;

    if ( sum2 > 21 )
    {
        for ( int i = 0; i < count; i++ )
        {
            if ( cards[i] == 11 )
            {
                cards[i] = 1;
                cout << "switched to 1!" << endl;
            }
        }
    }

    int sum3 = 0;
    sum3 = std::accumulate(cards, cards+3, sum3);
    cout << "sum3 is: " << sum3 << endl;

    return 0;
}