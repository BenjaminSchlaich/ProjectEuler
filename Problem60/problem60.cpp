
#include "../useful.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

static const int limit = 100000000;

inline int MAX(int a, int b)
{
    return a > b ? a : b;
}

// performs a lookup in the primes table
bool primecheck(int n);

// returns true <=> p++q is prime and q++p is prime
bool primePair(int p, int q);

// solve the problem for a set of N primes
void solve(int N);

int main()
{
    // precompute primes below 10^9
    primesieve::setStepsize(limit/100);
    primesieve::isPrime(limit);
    
    cout << "precomputed primes up to excluding " << limit << "." << endl;

    solve(5);

    return 0;
}

void solve(int N)
{
    int maxSetSize = 1;
    int orderOfMagnitude = 10;
    int minSetSum = std::numeric_limits<int>::max();
    list<list<int>> sets;
    auto itP = primesieve::knownPrimes().begin();

    while(itP != primesieve::knownPrimes().end() && (maxSetSize <= N /*|| *itP < minSetSum*/))  // the best set cannot contain a prime larger that the current best sum
    {
        list<list<int>> newSets;
        list<int> l;
        l.push_back(*itP);
        newSets.push_back(l);               // first value is the sum of the set
        newSets.front().push_back(*itP);    // then come the values

        for(auto s: sets)
        {
            bool prop = true;

            for(auto p = next(s.begin()); p != s.end(); p++)
                if(!primePair(*p, *itP))
                {
                    prop = false;
                    break;
                }
            
            if(prop)
            {
                list<int> ss(s);        // we can extend the old set to form a new one
                ss.push_back(*itP);     // add the new prime to the set
                ss.front() += *itP;     // update the sum, too

                maxSetSize = MAX(maxSetSize, ss.size());

                if(ss.size() == N+1)
                    minSetSum = min(minSetSum, ss.front());
                
                newSets.push_back(ss);
            }
        }

        sets.append_range(newSets);

        if(*itP > orderOfMagnitude)
        {
            cout << "prime done: " << *itP << ", #sets: " << sets.size() << ", largest set: " << maxSetSize << endl;
            orderOfMagnitude *= 10;
        }

        itP++;
    }

    if(minSetSum == numeric_limits<int>::max())
        cout << "no solution found, more primes are necessary." << endl;
    else
        cout << "lowest sum: " << minSetSum << endl;
}

bool primePair(int p, int q)
{
    return primecheck(stoi(to_string(p) + to_string(q))) && primecheck(stoi(to_string(q) + to_string(p)));
}

bool primecheck(int n)
{
    if(n >= limit)
        return isPrime(n);
    else
        return primesieve::isPrime(n);
}
