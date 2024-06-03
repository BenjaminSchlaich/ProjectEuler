
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPrime(int n)                     // naive prime test in O(sqrt(n))
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

// compiled with: clang++ problem50.cpp -o problem50 -std=c++20 -O2
int main(int argc, char *argv[])
{
    const int limit = 1000000;          // search limit
    vector<int> primes;                 // precompute the primes
    vector<long> prefixSums = {0};      // precompute the prefix sums of the primes

    for(int i=1; i<limit; i++)
        if(isPrime(i))
            primes.push_back(i);
    
    for(int i=1; i<=primes.size(); i++)
        prefixSums.push_back(prefixSums.at(i-1) + primes.at(i-1));
    
    int longestRange = 0;
    int bestPrime = 0;

    // outer loop, O(n) iterations
    for(auto i=prefixSums.begin() + 1; i != prefixSums.end(); i++)
    {
        // the sum must be smaller that limit, O(log(n))
        vector<long>::iterator sumStart = lower_bound(prefixSums.begin(), i, *i - limit + 1);

        // the sum must be longer than the current best
        vector<long>::iterator sumEnd = i - longestRange;
        
        // inner loop, O(n) iterations, but with the above cutoffs
        for(auto j=sumStart; j<sumEnd; j++)
            if(binary_search(primes.begin(), primes.end(), *i - *j))    // prime in O(log(n))
            {
                longestRange = i - j;
                bestPrime = *i - *j;
            }
    }

    cout    << endl << "The best prime below " << limit << " is " << bestPrime
            << ", as it can be summed up from " << longestRange << " consecutive primes." << endl;

    return 0;
}
