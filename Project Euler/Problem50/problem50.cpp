
#include "../useful.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

static const int L = 4;

// just because i'm curious what's faster when, here
void timePrimeChecks();

void solve(int limit);

void spacer();

int main(int argc, char *argv[])
{
    ///*
    solve(100);

    spacer();

    solve(1000);

    spacer();

    solve(1000000);//*/

    // timePrimeChecks();

    return 0;
}

void timePrimeChecks()
{
    spacer();

    cout << "running timePrimeChecks()..." << endl;

    vector<unsigned long> primes;

    vector<unsigned long> levels = {1000000, 2000000, 3000000, 4000000, 5000000};

    random_device rd;
    mt19937_64 mt(rd());
    const size_t N = 100000;       // number of samples to test

    // precompute the primes
    cout << "Starting to precompute the primes between " << levels.front() << " and " << levels.back() << "..." << endl;

    for(size_t i=levels.front(); i<=levels.back(); i++)
        if(isPrime(i))
            primes.push_back(i);

    cout << "Precomputing primes done. Starting to run tests now..." << endl;

    spacer();
    
    // test all ranges of levels and compare the speeds
    for(int l=1; l<levels.size(); l++)
    {
        unsigned long start = levels.at(l-1);
        unsigned long end = levels.at(l);

        // prepare uniformly distributed samples in the current range
        vector<unsigned long> samples;
        uniform_int_distribution<unsigned long> uDist(start, end);

        for(size_t i=0; i<N; i++)
            samples.push_back(uDist(mt));
        
        // measure the time for the standart prime check:
        cout << "running standart prime test on " << N << " random samples in the range from " << start << " to " << end << "." << endl;

        unsigned long countBasic = 0;

        chrono::time_point t0 = chrono::high_resolution_clock::now();

        for(unsigned long n: samples)
            if(isPrime(n))
                countBasic++;
        
        chrono::time_point t1 = chrono::high_resolution_clock::now();

        auto elapsedMS = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

        // print status information of the run
        cout << "Time elapsed: " << elapsedMS << "ms." << endl;
        cout << "Checksum: " << countBasic % 100 << endl;

        cout << endl << endl << endl;

        // measure the time for the precomputed lookup check:
        cout << "running prime lookup on " << N << " random samples in the range from " << start << " to " << end << "." << endl;

        unsigned long countLookup = 0;

        // find the correct starting position for the prime lookup, to be fair
        auto pStart = lower_bound(primes.begin(), primes.end(), start);
        
        // find the correct ending position, too...
        auto pEnd = upper_bound(primes.begin(), primes.end(), end);

        t0 = chrono::high_resolution_clock::now();

        for(unsigned long n: samples)
            if(binary_search(pStart, pEnd, n))
                countLookup++;
        
        t1 = chrono::high_resolution_clock::now();

        elapsedMS = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

        // print status information of the run
        cout << "Time elapsed: " << elapsedMS << "ms." << endl;
        cout << "Checksum: " << countBasic % 100 << endl;

        spacer();
    }
}

void spacer()
{
    cout << endl << endl << endl;

    for(int i=0; i<100; i++)
        cout << '-';
    
    cout << endl << endl << endl << endl;
}

void solve(int limit)
{
    vector<int> primes;

    for(int i=1; i<limit; i++)
        if(isPrime(i))
            primes.push_back(i);
    
    cout << "There are " << primes.size() << " primes below " << limit << endl;

    vector<long> prefixSums(primes.size() + 1);

    prefixSums.at(0) = 0;

    for(int i=1; i<=primes.size(); i++)
        prefixSums.at(i) = prefixSums.at(i-1) + primes.at(i-1);
    
    cout << "Computed all the prefix sums now, to reduce from O(n^3) to O(n^2)." << endl;

    int longestRange = 0;
    int bestPrime = 0;

    for(auto i=prefixSums.begin() + 1; i != prefixSums.end(); i++)
    {
        // the j-th prefix-sum must be at least big enough, that when subtracted from the i-th, the result is smaller than limit:
        //      prefixSums.at(i) - prefixSums.at(j) < limit <=> -prefixSums.at(j) < limit - prefixSums.at(i)
        // <=>  prefixSums.at(j) > prefixSums.at(i) - limit
        vector<long>::iterator sumStart;

        if(*i >= limit)
            sumStart = lower_bound(prefixSums.begin(), i, *i - limit);
        else
            sumStart = prefixSums.begin();

        // as lower_bound only ensures prefixSums.at(j) >= prefixSums.at(i) - limit, but <limit> is not included:
        if(*i - *sumStart == limit)
            sumStart++;
        
        // there must be at least as many elements in the sum, as in the best that we've found so far:
        vector<long>::iterator sumEnd = i - longestRange;
        
        for(auto j=sumStart; j<sumEnd; j++)                                                       // only look for better ranges
            if(binary_search(primes.begin(), primes.end(), *i - *j))                                        
            {
                longestRange = i - j;
                bestPrime = *i - *j;
            }
    }

    cout << endl << "The best prime below " << limit << " is " << bestPrime << ", as it can be summed up from " << longestRange << " consecutive primes." << endl;

    return;
}
