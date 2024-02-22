// Problem31.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using std::cout;
using std::endl;

int nCoins = 8;
int coins[8] = {200, 100, 50, 20, 10, 5, 2, 1};

int useCoins(int coin, int sum)
{
    if(coin >= nCoins)  // cannot make money with imaginary coins
        return 0;

    int times = 0;
    int ways = 0;

    while(coins[coin]*times + sum <= 200)
    {
        if(coins[coin]*times + sum == 200)
            ways++;
        else
            ways += useCoins(coin + 1, sum + coins[coin]*times);
        
        times++;
    }

    return ways;
}

int main()
{
    cout << "There are " << useCoins(0, 0) << " ways to make 2£ using the given coins." << endl;

    return 0;
}