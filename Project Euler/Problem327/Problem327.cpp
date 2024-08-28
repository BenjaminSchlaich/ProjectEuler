// Problem327.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>   // transport() needs this
#include <list>
#include <cmath>	// round()

using namespace std;

int solve(int C, int N, int K = 0)
{
    if(N == 0)
        return 0;
    
    int lastStep;

    if(K <= C-2)
        lastStep = 1;

    lastStep = 2 * (K/(C-2));

    if(K % (C-2) != 0)
        lastStep++;
    
    return lastStep + solve(C, N-1, lastStep);
}

/**
 * compile:
 * clang++ -Wall -pedantic -ferror-limit=1 -std=c++2b -o Problem327/problem327 'Problem327/Problem327.cpp'
 */
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "invoke like so: ./problem327 <maximum number of cards> <number of rooms>" << endl;
        return 0;
    }

    int C = stoi(argv[2]);
    int N = stoi(argv[1]);

    if(N <= 0 || C <= 0)
    {
        cout << "invalid arguments: " << C << ", " << N << " must both be greater or equal to 0." << endl;
        return 0;
    }

    int solution = solve(C, N);

    if(solution < 0)
        cout << "No solution was found." << endl;
    else
        cout << "M = " << solution << endl;
    
    return 0;
}
