
#include "solve.hpp"

#include <vector>

using namespace std;

inline constexpr int min(const int a, const int b)
{
    return a < b ? a : b;
}

inline constexpr int max(const int a, const int b)
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
    int r = min(K + 1, C) + max(0, K - (C-1)) * 3;
    return r;
}

int solve(int C, int R, int K)
{
    if(R == 1)
        return carryOne(C, K);
    else
        return solve(C, R-1, carryOne(C, K));
}
