
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int solve()
{
    vector<int> dp(101, 0);

    dp[1] = 1;
    dp[2] = 2;

    for(int i=3; i<=100; i++)
    {
        int x = 1;

        for(int j=1; j<=i/2; j++)
            x += dp[j];
    }

    return 0;
}

/**
 * build:
 * clang++ -std=c++20 -o problem76 -ferror-limit=1 problem76.cpp
 * 
 * run:
 * ./problem79
 */
int main()
{
    cout << "solution: " << solve();

    return 0;
}
