
#include <iostream>

#include "../useful.hpp"

using namespace std;

int main()
{
    long counter = 0;
    long dMax = 1000000;

    vector<long> phi = findPhi(dMax);

    for(long d=dMax; d>1; d--)
        counter += phi.at(d);
    
    cout << counter << endl;
}
