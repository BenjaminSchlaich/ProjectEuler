
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <functional>

static constexpr int TARGET = 4;
static constexpr bool DEBUG = true;

using namespace std;

/**
 * 2 -> 1
 * 3 -> 1
 * 4 = 2 + 2 -> 1
 * 5 = 2 + 3 -> 2
 * 6 = 3 + 3 -> 1
 * 7 = 2 + 5 -> 3
 * 11 = 
 */



/**
 * How many ways are there to sum up to n using up to k >= 0 variables assuming values in {0, 1, ... }?
 */
int sumsOf(int n, int k)
{
    if(k < 2)           // by the definition of the problem
        return 0;
    else if(n < k)      // because variables mustn't be 0
        return 0;
    else if(n <= 0)     // likewise, because variables mustn't be 0
        return 0;
    else if(k == 2)     // this is the base case
        return n + 1;
    else if(n == k)     // this is a shortcut to 1 + 1 + ... + 1 (n times)
        return 1;
    else
    {
        int c = 0;

        for(int x=1; x<n-k+1; x++)
            c += sumsOf(n - x, k - 1);
        
        return c;
    }
}

int solve()
{
    
}

/**
 * compile:
 * clang++ -std=c++2b -o Problem77/problem77 -Werror -Wall -fsanitize=address Problem77/problem77.cpp
 * 
 * run:
 * ./Problem77/problem77
 */
int main()
{
    for(int n=1; n<)
}

/**
 * 12 = 2 + 10
 * 12 = 3 + 9
 * 12 = 5 + 7
 * --------------
 * 12 = 2 + 2 + 8
 * 12 = 2 + 3 + 7
 * 12 = 2 + 5 + 5
 * 12 = 3 + 2 + 7
 * 12 = 3 + 3 + 6
 * 12 = 3 + 5 + 4
 * 12 = 5 + 2 + 5
 * 12 = 5 + 3 + 4
 * 
 * dp(n, p) := #ways to build n from primes <= p => dp(n, n) = dp(n)
 * dp(n, p) := sum(p_i ∈ {p_1, ..., p}) dp(n-p_i, p_i)
 */