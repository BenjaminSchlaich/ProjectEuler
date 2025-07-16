
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

namespace std{
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     http://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
          }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0>
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            hash_combine(seed, std::get<0>(tuple));
          }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>> 
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {                                              
            size_t seed = 0;                             
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);    
            return seed;                                 
        }                                              

    };
}

using namespace std;

static unordered_map<tuple<int, int, int>, int> memo;

/**
 * How many unique ways are there to sum up to n using exactly k >= 0 variables assuming values in {0, 1, ... , max}?
 */
int sumsOf(int n, int k, int max)
{
    if(k < 0)                       // by the definition of the problem this makes no sense
        return 0;
    else if(n < 0)                  // likewise doesn't make sense, since we don't have negative summands
        return 0;
    else if(n == 0)                 // the only way to achieve this is to set all variables to 0
        return 1;
    else if(k == 0 || max == 0)     // for n > 0 we would need some positive variables
        return 0;
    else if(n > k*max)              // this is a simple upper bound
        return 0;
    else if(n == 1)                 // there is only one way here: set one first variable to one and the others to 0
        return 1;
    else if(k == 1)                 // there is only one way here: set the variable to n
        return 1;
    else
    {
        // try memoization
        if(memo.contains({n, k, max}))
            return memo.at({n, k, max});

        int c = 0;

        for(int x=0; x<=max; x++)
            c += sumsOf(n - x, k - 1, x);
        
        // add to memo
        memo.insert({{n, k, max}, c});
        
        return c;
    }
}

int solve()
{
    return sumsOf(100, 100, 100) - 1;
}

/**
 * build:
 * clang++ -std=c++2b -o Problem76/problem76 -ferror-limit=1 -Werror -Wall Problem76/problem76.cpp
 * 
 * run:
 * ./Problem76/problem76
 * 
 * run:
 * ./problem79
 */
int main()
{
    cout << "solution: " << solve() << endl;

    return 0;
}
