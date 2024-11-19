
#include "solve.hpp"

#include <vector>

using namespace std;

inline constexpr unsigned long MIN(const unsigned long a, const unsigned long b)
{
    return a < b ? a : b;
}

inline constexpr unsigned long MAX(const unsigned long a, const unsigned long b)
{
    return a > b ? a : b;
}

// static vector<vector<unsigned long>> dp;

/**
 * // dp[r][c] = #cards necessary to carry c cards through r doors
    dp = vector<vector<unsigned long>>(R + 1, vector<unsigned long>());
 */

/**
 * how many cards are needed to carry c cards through 1 door?
 */
unsigned long carryOne(unsigned long C, unsigned long K)
{
    if(C <= 2 && K >= 1)
        throw logic_error("carryOne called with impossible arguments: C=" + to_string(C) + " K=" + to_string(K));
    
    if(K < C)
        return K + 1;
    
    unsigned long ceilw = (K - C + 1) % (C - 2);
    unsigned long walks = (K - C + 1) / (C - 2);

    if(ceilw)
        walks++;

    unsigned long spill = K - walks * (C - 2);
    
    return walks * C + spill + 1;
}

unsigned long solve(unsigned long C, unsigned long R, unsigned long K)
{
    if(R == 1)
        return carryOne(C, K);
    else
        return solve(C, R - 1, carryOne(C, K));
}
