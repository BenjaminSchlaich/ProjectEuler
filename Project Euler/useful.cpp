
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

long power(long n, long e)
{
    long p = 1;

    while(e > 0)
    {
        p *= n;
        e--;
    }

    return p;
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

long properDivisors(long n)
{
    if(n <= 2)
        return 0;

    int count = 0;

    for(int k=2; k*k<=n; k++)
        if(n % k == 0)
            count++;
    
    return count;
}

std::vector<std::pair<long, long>> primeFactorization(long n)
{
    if(n < 2)
        return {};
    else if( n == 2)
        return {{2, 1}};
    
    std::vector<std::pair<long, long>> factorization;

    if(n % 2 == 0)
    {
        factorization.push_back({2, 0});

        while(n % 2 == 0)
        {
            factorization.back().second++;
            n /= 2;
        }
    }

    if(n % 3 == 0)
    {
        factorization.push_back({3, 0});

        while(n % 3 == 0)
        {
            factorization.back().second++;
            n /= 3;
        }
    }

    int k = 5;
    bool add2 = true;

    while(n > 1)
    {
        if(n % k == 0)
        {
            factorization.push_back({k, 0});

            while(n % k == 0)
            {
                factorization.back().second++;
                n /= k;
            }
        }

        if(add2)
            k += 2;
        else
            k += 4;
        
        add2 = !add2;
    }

    return factorization;
}

std::string factorizationToString(std::vector<std::pair<long, long>> f)
{
    std::string s = "{";

    for(int i=0; i<f.size(); i++)
    {
        s += std::to_string(f.at(i).first) + "^" + std::to_string(f.at(i).second);

        if(i < f.size()-1)
            s += " * ";
    }

    return s + "}";
}

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

std::ostream &operator<<(std::ostream &os, std::list<int> &l)
{
    os << "[";

    for(auto it=l.begin(); it!=l.end(); it++)
        os << *it << (next(it) != l.end() ? ", " : "");
    
    os << "]";

    return os;
}

std::list<std::string> permutations(std::string s)
{
    if(s.empty())
        return {""};
    
    std::list<std::string> ps;

    for(auto it=s.begin(); it!=s.end(); it++)
    {
        char c = *it;

        s.erase(it);

        std::list<std::string> ss = permutations(s);

        for(auto &s: ss)
            s.insert(s.begin(), c);
        
        ps.append_range(ss);

        s.insert(it, c);
    }

    return ps;
}

bool isPermutation(std::string s1, std::string s2)
{
    if(s1.size() != s2.size())
        return false;
    
    for(char c: s1)
    {
        bool found = false;

        for(auto it=s2.begin(); it!=s2.end(); it++)
            if(*it == c)
            {
                s2.erase(it);
                found = true;
                break;
            }
        
        if(!found)
            return false;
    }

    return true;
}

std::vector<long> findPhi(long limit)
{
    std::vector<long> v(limit+1, 1);

    for(long n=2; n<=limit; n++)
    {
        if(v.at(n) == 1)
        {
            long m=n;

            while(m <= limit)
            {
                long e=0;
                long l = m;

                do
                {
                    l = l/n;
                    e++;
                } while(l % n == 0);

                v.at(m) *= (n-1) * power(n, e-1);

                m += n;
            }
        }
    }

    return v;
}

long safegcd(long a, long b)
{
    if(b == 0)
        return a;
    else
        return safegcd(b, a % b);
}

long gcd(long a, long b)
{
    if(a > b)
        return safegcd(a, b);
    else
        return safegcd(b, a);
}