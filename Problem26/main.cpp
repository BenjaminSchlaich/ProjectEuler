
#include <iostream>
using std::cout;
using std::endl;

#include <unordered_map>

#include <iomanip>

// for an integer n, returns the length of the reciprocal cycle of 1/n, or 0, if it doesn't exist
int solve(int n)
{
    int rest = 1;
    int iteration = 0;

    // contains remainders, and the iteration they were computed in.
    std::unordered_map<int, int> hashtable;

    while(rest != 0)
    {
        hashtable.insert({rest, iteration});

        while(rest < n)
            rest *= 10;
        
        rest = rest % n;
        
        iteration++;
        
        if(hashtable.contains(rest))
            return iteration - hashtable.find(rest)->second;
        else
            hashtable.insert({rest, iteration});
    }

    // no cycle has been found, and we're done computing the decimal fraction.
    return 0;
}

int main()
{
    int max = 0;
    int dMax = 0;

    for(int d=1; d<1000; d++)
    {
        int len = solve(d);

        if(len > max)
        {
            max = len;
            dMax = d;
        }
    }

    cout << "The longest reciprocal cycle found is for d = " << dMax << endl;

    return 0;
}
