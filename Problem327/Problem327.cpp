// Problem327.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "solve.hpp"

#include <iostream>

using namespace std;

/**
 * build:
 * flg="-std=c++2b -Wall -Werror -ferror-limit=1 -o problem327"
 * src="solve.cpp problem327.cpp"
 * build="clang++ $flg $src"
 * eval $build
 * 
 * run:
 * ./problem327
 */
int main()
{
    for(int n=1; n<=9; n++)
    {
        for(int r=1; r<= (n <= 4 ? 2 : 1); r++)
            cout << solve(3, r, n) << " ";
        
        cout << endl;
    }

    cout << "M(3, 6) = " << solve(3, 6) << endl;
}
