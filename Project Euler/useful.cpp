
#include "useful.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

void spacer(int newlines)
{
    for(int i=0; i<newlines; i++)
        std::cout << std::endl;

    for(int i=0; i<100; i++)
        std::cout << '-';
    
    for(int i=0; i<newlines; i++)
        std::cout << std::endl;
}

template <std::ranges::range T>
std::ostream &operator<<(std::ostream &os, T r)
{
    os << "[";

    auto it = r.begin();

    if(it != r.end())
        os << *it++;
    
    while(it != r.end())
        os << " ," << *it++;
    
    os << "]";

    return os;
}

bool isPrime(int n)
{
    if(n < 2)
        return false;
    else if(n == 2)
        return true;
    else if(n % 2 == 0)
        return false;
    
    int limit = (int) ceil(sqrt(n));

    for(int t=3; t<=limit; t++)
        if(n % t == 0)
            return false;
    
    return true;
}

long primesieve::stepSize = 1000000;                        // this can be any number >= 1
long primesieve::limit = 2;                                 // this must be 2, for the whole algorithm to work!
std::vector<long> primesieve::primes = std::vector<long>();

bool primesieve::isPrime(long n)
{
    if(n < 2)
        return false;
    else if(n < limit)
        return std::binary_search(primes.begin(), primes.end(), n);
    else
    {
        long sieveStart = limit;

        long augmentations = (n - limit) / stepSize + 1;

        long K = augmentations * stepSize;

        limit += K;

        std::vector<bool> sieve(K, true);

        // first cross out all multiples of the already known primes:
        for(long p: primes)
        {
            long mult = sieveStart / p + (sieveStart % p == 0 ? 0 : 1); // the first multiplicity of p in the range [sieveStart, inf)

            while(p*mult < limit)                                        // cross out all further multiplicities in the range [sieveStart, limit)
            {
                sieve.at(p*mult - sieveStart) = false;
                mult++;
            }
        }

        // next cross out all multiples of the primes in the range itself:
        for(long k=0; k<K; k++)
        {
            if(!sieve.at(k))            // this number has been crossed out before
                continue;
            
            long p = k + sieveStart;    // n must be a prime then
            long mult = 2;

            while(p*mult < limit)
            {
                sieve.at(p*mult - sieveStart) = false;
                mult++;
            }
        }

        // finally, add all the primes that were newly gained to our vector:
        for(long k=0; k<K; k++)
            if(sieve.at(k))
                primes.push_back(sieveStart + k);

        // this one time, we can look up the result in O(1)
        return sieve.at(n - sieveStart);
    }
}

void primesieve::setStepsize(long stepSize)
{
    primesieve::stepSize = stepSize;
}

const std::vector<long> &primesieve::knownPrimes()
{
    return primes;
}

template std::ostream &operator<<(std::ostream &os, std::vector<int> v);
template std::ostream &operator<<(std::ostream &os, std::list<int> v);