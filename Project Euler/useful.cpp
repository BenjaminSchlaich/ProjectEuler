
#include "useful.hpp"

#include <cmath>

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
