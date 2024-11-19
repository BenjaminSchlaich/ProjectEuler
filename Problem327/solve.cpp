
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

    int res = 0;

    while(K > 0)
    {
        if(K < C)
            return res + K + 1;
        else
        {
            K -= C - 2;
            res += C;
        }
    }

    return res;
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
