
#include "../useful.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

static const int limit = 10000;
static vector<int> primes;

// performs a lookup in the primes table
bool primecheck(int n);

// returns true <=> p++q is prime and q++p is prime
bool primePair(int p, int q);

// solve the problem for a set of N primes
void solve(int N);

int main()
{
    // precompute primes:
    for(int n=2; n<=limit; n++)
        if(isPrime(n))
            primes.push_back(n);
    
    cout << "precomputed " << primes.size() << " primes up to " << limit << "." << endl;

    solve(4);

    return 0;
}

void solve(int N)
{
    // now find the set
    unordered_map<int, vector<int>> combis;

    // find pairs for primes
    for(auto it=primes.begin(); it != primes.end(); it++)
    {
        for(auto it2=it+1; it2 != primes.end(); it2++)
        {
            if(primePair(*it, *it2))
            {
                if(!combis.contains(*it))
                    combis.insert({*it, {*it2}});
                else
                    combis.at(*it).push_back(*it2);
            }
        }
    }

    auto it = combis.begin();

    while(it != combis.end())
        if(it->second.size() < N - 1)
            it = combis.erase(it);
        else
            it++;

    cout << "There are " << combis.size() << " primes with at least " << N << " pairs:" << endl;

    for(auto pair: combis)
        cout << pair.first << ": " << pair.second << endl;
}

bool primePair(int p, int q)
{
    return primecheck(stoi(to_string(p) + to_string(q))) && primecheck(stoi(to_string(q) + to_string(p)));
}

bool primecheck(int n)
{
    return binary_search(primes.begin(), primes.end(), n);
}
