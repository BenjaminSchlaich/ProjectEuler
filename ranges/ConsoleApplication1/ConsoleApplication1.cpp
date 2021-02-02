// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Table.h"

using namespace rangeslib;

int main()
{
    int x, y, z;

    Table<int>::add(0, x, 10);
    Table<int>::add(1, y, 9);
    Table<int>::add(3, z, true);

    x = 0;
    y = 0;
    std::cout << rangeslib::Table<int>::check(x);
    std::cout << Table<int>::get(z);

    //removeRange(x);
    addRange(4, x, 100);

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
