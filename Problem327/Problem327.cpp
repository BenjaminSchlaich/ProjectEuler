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

int main()
{
    test_all();

    cout << "Result of the small sum (3 <= C <= 10, R = 6):" << endl;
    
    unsigned long sum = 0;

    for(unsigned long C=3; C<=10; C++)
        sum += solve(C, 10);
    
    cout << sum << endl;
    
    cout << endl << "C=3, R=30:" << endl;

    cout << solve(3, 30) << endl;

    cout << endl << "Solution of the problem (3 <= C <= 40, R = 30):" << endl;

    sum = 0;

    for(unsigned long C=3; C<=40; C++)
        sum += solve(C, 30);
    
    cout << sum << endl;
    
    return 0;
}
