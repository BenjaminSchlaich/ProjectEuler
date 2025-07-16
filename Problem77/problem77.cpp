
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <functional>

static constexpr int TARGET = 4;
static constexpr bool DEBUG = true;

using namespace std;


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