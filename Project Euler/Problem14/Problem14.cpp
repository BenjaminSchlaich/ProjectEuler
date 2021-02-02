// Problem14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

typedef unsigned long long ull;

ull coll(ull n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

int main()
{
    int maxR = 0;
    ull maxN = 0;
    for (int i = 1; i < 1000000; i++)
    {
        int r = 0;
        ull n = i;
        ull startN = i;
        while (n != 4)
        {
            n = coll(n);
            r++;
        }

        if (r > maxR)
        {
            maxR = r;
            maxN = startN;
        }
    }

    std::cout << maxN << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
