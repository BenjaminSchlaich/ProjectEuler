
#pragma once

#include <fstream>
#include <ranges>
#include <vector>
#include <list>

// print integer list
std::ostream &operator<<(std::ostream &os, std::list<int> &l);

// precomputes euler's totient function (phi) for n ∈ {1, ..., limit} and stores it in the result vector.
std::vector<long> findPhi(long limit);

// returns a list of all permutations of s, including s (identity).
std::list<std::string> permutations(std::string s);

// checks whether one string is a permutation of the other
bool isPermutation(std::string s1, std::string s2);

// nice for printing some space
void spacer(int newlines = 3);

// simple integer exponentiation
long power(long n, long e);

// simple prime check in O(sqrt(n)) complexity.
bool isPrime(int n);

// number of proper (not 1 or n) divisors in O(sqrt(n))
long properDivisors(long n);

// euclid's algorithm to compute greatest common divisor
long gcd(long a, long b);

std::vector<std::pair<long, long>> primeFactorization(long n);

std::string factorizationToString(std::vector<std::pair<long, long>> f);

/**
 * Erathosthenes prime sieve that caches primes in a static class.
 * This is only fast for loads of prime checks in the same region,
 * as otherwise the naive prime check above vastly outperforms it.
 * Lookup for previously tested primes in O(log(n))
*/
class primesieve
{
    public:

    static bool isPrime(long n);                    // returns true if n is a prime number.

    static void setStepsize(long stepSize);         // update the stepsize to be used for future augmentations

    static const std::vector<long> &knownPrimes();  // returns the currently known primes.

    private:

    static long stepSize;                       // by how much to increase the range of the sieve, when asked for a number that occurred already.

    static long limit;                          // the current limit of the sieve (initially == stepsize)

    static std::vector<long> primes;            // all primes that have been found so far.
};
