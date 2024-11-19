
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
    if(C <= 2 && K >= 1)
        throw logic_error("carryOne called with impossible arguments: C=" + to_string(C) + " K=" + to_string(K));
    else if(K < C)
        return K + 1;
    else
        return K / (C - 2) * C + (K % (C - 2)) + 1;
}

int solve(int C, int R, int K)
{
    if(R == 1)
        return carryOne(C, K);
    else
        return solve(C, R - 1, carryOne(C, K));
}
