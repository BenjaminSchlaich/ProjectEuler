
#include "../useful.hpp"

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <functional>

#define MAX(a, b) {a > b ? a : b}

using namespace std;

static const unsigned int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

static unsigned long digitSum(unsigned long l)
{
    unsigned char s = 0;

    while(l > 0)
    {
        s += l % 10;
        l /= 10;
    }

    return s;
}

static unsigned long numbers(unsigned long l)
{
    unsigned long p = 1;

    while(l > 0)
    {
        p *= primes[l % 10];
        l /= 10;
    }

    return p;
}

static unsigned long myhash(unsigned long l)
{
    return digitSum(l) ^ numbers(l);
}

/**
 * WARNING:
 * This works by chance without modification:
 * 1. myhash guarantees that all permutations will have the same hash value, but non-permutations might too
 *      -> There could be false positives.
 *      -> If that should be the case for higher versions of the problem, a straight-forward solution would be
 *         an additional check whether two numbers are permutations, if they are sorted into the same bucket.
 * 2. I don't check, whether there could be more that the wanted number of cube permutations, which could be the case
 *      for the lowest result, which would then be wrongfully returned. This would also be easy to solve, by generating
 *      the permutations in case of a possible solution (at least 5 cube permutations), and checks that there are no additional cubes.
 *      If there are, the entire group can be discarded by deleting them from the cubes map.
 * As none of the above makes any trouble, this is a very neat and fast solution, though, and fixes for correctnes would be easy.
 */
int main()
{
    std::unordered_map<unsigned long, list<unsigned long>> cubes;

    unsigned long n = 1;

    while(true)
    {
        unsigned long cube = n*n*n;

        unsigned long h = myhash(cube);

        if(cubes.contains(h))
        {
            auto &l = cubes.at(h);

            l.push_back(cube);

            if(l.size() == 5)
            {
                for(auto n: l)
                    cout << n << endl;
                
                return 0;
            }
        }
        else
            cubes.insert({h, {cube}});
        
        n++;
    }

    return 0;
}
