
#include <iostream>
#include <vector>

#include "../useful.hpp"

using namespace std;

int main()
{
    long N = 1000000;
    vector<long> phi = findPhi(N);

    double iMax = 0;
    double max = 0;

    for(long n=1; n<=N; n++)
    {
        double d = ((double) n) / phi.at(n);
        
        if(d > max)
        {
            iMax = n;
            max = d;
        }
    }

    cout << "Max: " << max << ", n = " << iMax << endl;

    return 0;
}
