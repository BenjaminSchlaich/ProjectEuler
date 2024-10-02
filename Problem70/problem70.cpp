
#include <iostream>

#include "../useful.hpp"

using namespace std;

int main()
{
    long N = 10000000;   // 10^7

    vector<long> phi = findPhi(N);

    cout << "Precomputed phi up to " << N << endl;

    vector<long> candidates;

    for(long n=2; n<=N; n++)
        if(isPermutation(to_string(n), to_string(phi.at(n))))
            candidates.push_back(n);
    
    cout << "There are " << candidates.size() << " candidates, the first of which is " << candidates.front() << endl;

    double min = numeric_limits<double>::max();
    long minI = 0;

    for(long k: candidates)
    {
        double d = ((double) k) / phi.at(k);

        if(d < min)
        {
            min = d;
            minI = k;
        }
    }

    cout << "The solution is " << minI << ", where n/phi(n) = " << min << endl;

    return 0;
}
