// Problem327.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>   // howManyCards() needs this

using namespace std;

// calculate how many cards we need to get through r rooms with card limit c
int howManyCards(int c, int r);

// calculate how many cards we need to bring x cards into a room r rooms ahead going room-by-room with card limit c
int bringCards(int x, int r, int c)
{
    if (r == 1)
        return 2 * x / (c - 2);
    else
        return 2 * bringCards(x, r-1, c) / (c-2);
}

int main()
{
    int r = 6;
    int c = 3;
    cout << "to travel through " << r << " rooms with a card limit of " << c << " you need at least " << howManyCards(c, r) << " cards";

    for (int r = 1; r < 10; r++)
        cout << bringCards(1, r, 3) << endl;
}

int howManyCards(int c, int r)
{
    // the return value: the minimum of cards we need
    int minC = r - c + 1;   // at the end we run through
    
    int heavyR = minC;  // ...

    return bringCards(c-1, heavyR, c) + c + 1;
}
