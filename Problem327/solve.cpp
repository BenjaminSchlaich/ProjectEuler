
#include "solve.hpp"

#include <vector>

using namespace std;

inline constexpr int MIN(const int a, const int b)
{
    return a < b ? a : b;
}

inline constexpr int MAX(const int a, const int b)
{
    return a > b ? a : b;
}

static int C;
static vector<vector<int>> dp;

/**
 *  
 */

/**
 * how many cards are needed to carry K cards through 1 door?
 */
int carryOne(int K)
{
    int r = MIN(K + 1, C) + MAX(0, K - (C-1)) * 3;
    return r;
}

int solveThis(int R, int K)
{
    if(R == 1)
        return carryOne(K);
    
    int min = numeric_limits<int>::max();

    for(int r = 1; r < R; r++)
    {
        int secondPart = solveThis(R - r, 1);
        int whole = solveThis(r, secondPart) + secondPart;
        min = MIN(min, solveThis(r));
    }
    
    return carryOne(K) + solve(C, R-1, carryOne(K));
}

int solve(int c, int R, int K)
{
    C = c;

    // dp[r][c] = #cards necessary to carry c cards through r doors
    dp = vector<vector<int>>(R + 1, vector<int>());

    return solveThis(R, K);
}
