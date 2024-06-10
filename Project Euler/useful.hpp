
#pragma once

#include <fstream>
#include <ranges>
#include <vector>

// nice for printing some space
void spacer(int newlines = 3);

// allows printing of iterable classes as an array.
template <std::ranges::range T>
std::ostream &operator<<(std::ostream &os, T r);

// simple prime check in O(sqrt(n)) complexity.
bool isPrime(int n);

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
