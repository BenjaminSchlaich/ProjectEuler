
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

// static vector<vector<int>> dp;

/**
 * // dp[r][c] = #cards necessary to carry c cards through r doors
    dp = vector<vector<int>>(R + 1, vector<int>());
 */

/**
 * how many cards are needed to carry c cards through 1 door?
 */
int carryOne(int C, int K)
{
    int r = MIN(K + 1, C) + MAX(0, K - (C-1)) * 3;
    return r;
}

int solve(int C, int R, int K)
{
    if(R == 1)
        return carryOne(C, K);
    
    int min = numeric_limits<int>::max();

    for(int r=1; r<R; r++)
    {
        int back = solve(C, R - r, K);
        int whole = solve(C, r, back);
        min = MIN(min, whole);
    }

    return min; // solve(C, R-1, carryOne(C, K));
}
