
#include <iostream>

#include "../useful.hpp"

using namespace std;

typedef pair<long, long> fraction;

bool operator<=(fraction f1, fraction f2)
{
    return f1.first * f2.second <= f2.first * f1.second;
}

bool operator<(fraction f1, fraction f2)
{
    return f1.first * f2.second < f2.first * f1.second;
}

ostream &operator<<(ostream &os, const fraction &f)
{
    os << '(' << f.first << '/' << f.second << ')';

    return os;
}

// finds and returns the closest fraction to but not higher than <f>, with denominator <d>
fraction lowerBound(fraction f0, long d)
{
    long n=1;
    long rangemax = 1;
    
    while(fraction({n, d}) <= f0)           // exponential search for the upper bound
        rangemax = (n *= 2);
    
    if(n == 1)
        throw std::runtime_error("no fraction with denominator " + to_string(d)
                                +"can be smaller than " + to_string(f0.first) + '/' + to_string(f0.second));
    
    int rangemin = n/2;                     // we know for sure that n/2d <= limit

    while(rangemax - rangemin >= 10)        // cutoff for linear vs binary search
    {
        n = (rangemin + rangemax) / 2;      // perform binary search

        if(fraction({n, d}) < f0)
            rangemin = n;
        else
            rangemax = n;
    }

    n = rangemin;                           // reset to lower bound, bc true n might be everywhere in range

    while(n < rangemax)                     // linear search in small range
    {
        fraction f1({n+1, d});

        if(f1 < f0)
            n++;
        else
            break;
    }

    return {n, d};
}

// finds and returns the closest fraction to but not lower than <f>, with denominator <d>
fraction upperBound(fraction f0, long d)
{
    long n=1;
    long rangemax = 1;
    
    while(fraction({n, d}) < f0)            // exponential search for the upper bound
        rangemax = (n *= 2);
    
    if(n == 1)                              // 1/d >= f0, so we can return immediately
        return {n, d};
    
    int rangemin = n/2;                     // we just made sure that n/d <= limit

    while(rangemax - rangemin >= 10)        // cutoff for linear vs binary search
    {
        n = (rangemin + rangemax) / 2;      // perform binary search

        if(fraction({n, d}) < f0)
            rangemin = n;
        else
            rangemax = n;
    }

    n = rangemax;                           // reset to lower bound, bc true n might be everywhere in range

    while(n > rangemin)                     // linear search in small range
    {
        fraction f1({n-1, d});

        if(f0 < f1)
            n--;
        else
            break;
    }

    return {n, d};
}

int main()
{
    const fraction lowBound({1, 3});
    const fraction hghBound({1, 2});

    size_t count = 0;

    for(long d=4; d<=12000; d++)
    {
        int nMin = upperBound(lowBound, d).first;
        int nMax = lowerBound(hghBound, d).first;

        for(long n=nMin; n<=nMax; n++)
            if(gcd(n, d) == 1)
                count++;
    }

    cout << "solution: " << count << endl;
}
