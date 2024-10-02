
#include "../useful.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

vector<int> primes;

#define PRIMECHECK(n) binary_search(primes.begin(), primes.end(), n)

void solve(int limit);

int generate(int n);

// clang++ -std=c++2b -O2 -o Problem51/problem51 Problem51/problem51.cpp useful.cpp -Wall -pedantic
int main(int argc, char *argv[])
{
    solve(8);

    return 0;
}

int generate(int n)
{
    string s = to_string(n);    // n in string form
    int maxcount = 0;

    string digits;              // all the digits that occurr in n

    for(char c: s)              // find the digits to populate the string
        if(!digits.contains(c))
            digits.push_back(c);
    
    for(char c: digits)         // for each digit occurence, replace all these by all other possible digits
    {
        int count = 0;

        for(char cc = '0'; cc <= '9'; cc++)
        {
            if(cc == c || (c == digits.front() && cc == '0'))
                continue;
            
            string ss(s);

            for(auto it = ss.begin(); it != ss.end(); it++)
                if(*it == c)
                    *it = cc;
            
            if(PRIMECHECK(stoi(ss)))
                count++;
        }

        maxcount = max(maxcount, count);
    }

    return maxcount + 1;    // don't forget about n itself!
}

void solve(int digits)
{
    int limit = 10000000;

    for(int i=1; i<limit; i++)
        if(isPrime(i))
            primes.push_back(i);
    
    cout << "There are " << primes.size() << " primes below " << limit << endl;

    int count = 0;

    auto primeIt = primes.begin();

    while(primeIt != primes.end())
    {
        count = generate(*primeIt);

        if(count >= digits)
        {
            cout << "Found one conforming prime: " << *primeIt << endl;
            return;
        }
        
        primeIt++;
    }

    cout << "Found no prime that conforms." << endl;
    
    return;
}
