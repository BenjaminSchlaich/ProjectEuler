
/**
 * To build the project, enter the following lines one after another into the terminal:
 * libraryOptions="-L/Users/benjamin/Downloads/msieve-master -lmsieve -lgmp -lm -lpthread -I/Users/benjamin/Downloads/msieve-master/include"
 * build="clang++ $libraryOptions -std=c++2b -o Problem351/problem351 useful.cpp Problem351/problem351.cpp"
 * eval $build
 * 
 * To run the built executable, enter the following:
 * ./Problem351/problem351
 */
#include <iostream>
#include <unordered_set>
#include <chrono>
#include <fstream>
#include <list>
#include <string>

#include "../useful.hpp"

#include <msieve.h>
#include <util.h>

using namespace std;

typedef pair<int, int> fraction;

namespace std
{
    template <>
    struct hash<pair<int, int>>
    {
        size_t operator()(const pair<int, int> &p) const
        {
            return (((size_t) p.first) << 32) | p.second;
        }
    };
}

// euclid's algorithm for fraction simplification, where a >= b.
int gcd(int a, int b);

// returns the simplified fraction.
fraction simplify(const fraction &fraction);

// print a fraction
ostream &operator<<(ostream &os, fraction p);

// this works but only in O(N^2), which is far too slow for N=100'000'000!
int simpleH(int N)
{
    int hidden = 0;

    unordered_set<fraction> found;          // the representatives of the fractions so far

    for(int n=1; n<=N; n++)                 // iterate through all of the rings
    {
        fraction f = {2*n, 0};              // starting point on the x axis

        for(int i=0; i<n; i++)              // move up-left to the corner of the ring
        {
            fraction r = simplify(f);       // compute the representative of the fraction f

            if(found.contains(r))
                hidden++;
            else
                found.insert(r);
            
            f.first--;
            f.second++;
        }
    }

    return hidden * 6;
}

// euler's totient function
long phi(long n)
{
    auto f = primeFactorization(n);

    long res = 1;

    for(auto &factor: f)
        res *= (factor.first-1) * power(factor.first, factor.second-1);
    
    return res;
}

// O(n*sqrt(n)), still far too slow!
long S(long N)
{
    long hidden = 0;

    for(long k=2; k<=N; k++)
        hidden += k - phi(k) - 1;
    
    return (hidden + (N - 1)) * 6;
}

// print the measured times for the simpleH() function to the file simpleH.txt
void plotSimpleH()
{
    ofstream ofsSimpleH("Problem351/simpleH.txt");

    for(int i=500; i<=5000; i+=500)
    {
        int chksum = 0;
        auto t0 = std::chrono::high_resolution_clock::now();
        chksum += simpleH(i);
        auto t1 = std::chrono::high_resolution_clock::now();

        long ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        ofsSimpleH << i << " " << ms << endl;

        cout << "simpleH chksum: " << chksum << ", ";
    }

    ofsSimpleH.close();
}

// print the measured times for the S() function to the file S.txt
void plotS()
{
    ofstream ofsS("Problem351/S.txt");

    for(int i=10000; i<=100000; i+=10000)
    {
        long chksum = 0;
        auto t0 = std::chrono::high_resolution_clock::now();
        chksum += S(i);
        auto t1 = std::chrono::high_resolution_clock::now();

        long ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        ofsS << i << " " << ms << endl;

        cout << "S chksum: " << chksum << endl;
    }

    ofsS.close();
}

vector<long> do_factor(long n)
{
    char *nStr = new char[to_string(n).size()];

    uint32 randomSeed1 = rand();
    uint32 randomSeed2 = rand();
    uint32 maxRelations = 0;
    uint32 nfsLower = 0;
    uint32 nfsUpper = 0;
    uint32 l1CacheSize, l2CacheSize;
    char *savefileName = MSIEVE_DEFAULT_SAVEFILE;
    char *logfileName = MSIEVE_DEFAULT_LOGFILE;
    char *bfileName = MSIEVE_DEFAULT_NFS_FBFILE;

    get_cache_sizes(&l1CacheSize, &l2CacheSize);
    
    msieve_obj *mso = msieve_obj_new(nStr, 0, savefileName
                                    , logfileName, bfileName, randomSeed1
                                    , randomSeed2, maxRelations, nfsLower
                                    , nfsUpper, cpu_generic, l1CacheSize
                                    , l2CacheSize, 0, 0
                                    , 0);
    
    msieve_run(mso);

    msieve_factor *f = mso->factors;

    vector<long> facts;

    while(f != nullptr)
    {
        facts.push_back(stol(f->number));
        f = f->next;
    }

    return facts;
}

int main(int argc, char *argv[])
{
    long n = stol(argv[1]);

    cout << "Factorizing " << n << "..." << endl;

    auto fs = do_factor(n);

    cout << "Result:" << endl;

    for(long l: fs)
        cout << l << endl;

    return 0;
}

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

fraction simplify(const fraction &fraction)
{
    int large = max(fraction.first, fraction.second);
    int small = min(fraction.first, fraction.second);
    int d = gcd(large, small);
    return {fraction.first / d, fraction.second / d};
}

ostream &operator<<(ostream &os, fraction p)
{
    cout << p.first << "/" << p.second;
    return os;
}

/**
 * clang++ -L/Users/benjamin/Downloads/msieve-master/ -llibmsieve -I/Users/benjamin/Downloads/msieve-master/include -std=c++2b -o Problem351/problem351 useful.cpp Problem351/problem351.cpp
 */
