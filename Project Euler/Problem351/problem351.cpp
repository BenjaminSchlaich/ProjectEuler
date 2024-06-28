
#include <iostream>
#include <vector>

#include "../useful.hpp"

using namespace std;

long S(long N)
{
    cout << "running S()..." << endl;
    cout << "precomputing phi up to " << N << "..." << endl;

    auto ph = findPhi(N);

    cout << "phi fully computed." << endl;

    long hidden = 0;

    for(long k=2; k<=N; k++)
        hidden += k - ph.at(k) - 1;
    
    return (hidden + (N - 1)) * 6;
}

int main(int argc, char *argv[])
{
    long N = 100000000;

    cout << "computing S(" << N << ")..." << endl;

    long s = S(N);

    cout << "result: " << s << endl;
    
    return 0;
}
