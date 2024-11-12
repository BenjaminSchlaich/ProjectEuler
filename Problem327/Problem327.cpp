// Problem327.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "solve.hpp"
#include "test327.hpp"

#include <iostream>

using namespace std;

/**
 * /Users/benjaminschlaich/Coding/ProjectEuler/test.cpp
 * 
 * build:
 * flg="-std=c++2b -Wall -Werror -ferror-limit=1 -o problem327"
 * src="solve.cpp problem327.cpp test327.cpp"
 * build="clang++ $flg $src"
 * eval $build
 * 
 * run:
 * ./problem327
 */
int pmain()
{
    for(int n=1; n<=9; n++)
    {
        for(int r=1; r<= 2; r++)
            cout << solve(3, r, n) << " ";
        
        cout << endl;
    }

    cout << "M(3, 6) = " << solve(3, 6) << endl;
    cout << "M(4, 6) = " << solve(4, 6) << endl;

    return 0;
}

int main()
{
    test_all();

    return 0;
}
