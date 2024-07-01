
#define ARRLEN(a) sizeof(a) / sizeof(*a)

#include <iostream>
#include <set>

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

void testComparing()
{
    fraction fs[] = {{1,8}, {1,7}, {1,6}, {1,5}, {1,4}, {2,7}, {1,3}, {3,8}, {2,5}, {3,7}, {1,2}, {4,7}};

    cout << "      ";

    for(int i=0; i<ARRLEN(fs); i++)
        cout << fs[i] << ' ';

    for(int i=0; i<ARRLEN(fs); i++)
    {
        cout << endl << fs[i] << ' ';

        for(int j=0; j<ARRLEN(fs); j++)
        {
            if(fs[i] <= fs[j])
                cout << "  y   ";
            else
                cout << "  n   ";
        }
    }

    cout << endl;
}

// finds and returns the closest fraction to but not higher than <f>, with denominator <d>
fraction lowerBound(fraction f0, long d)
{
    long n=1;
    long rangemax = 1;
    
    while(fraction({n, d}) <= f0)             // exponential search for the upper bound
        rangemax = (n *= 2);
    
    if(n == 1)
        throw std::runtime_error("no fraction with denominator " + to_string(d)
                                +"can be smaller than " + to_string(f0.first) + '/' + to_string(f0.second));
    else
        n /= 2;
    
    int rangemin = n;                       // we just made sure that n/d <= limit

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

        if(!(f0 <= f1))
            n++;
        else
            break;
    }

    return {n, d};
}

int main()
{
    auto cmp = [](fraction a, fraction b){return a <= b;};

    set<fraction, decltype(cmp)> s;

    const long dMax = 1000000;

    const fraction limit = {3, 7};

    for(long d=dMax; d>2; d--)
    {
        // perform exponential/binary search for each denominator, to find the closest enumerator
        fraction f = lowerBound(limit, d);

        s.insert(f);
    }
    
    cout << "solution: " << *s.rbegin() << endl;
}
