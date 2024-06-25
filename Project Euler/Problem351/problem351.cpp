
#include <iostream>
#include <vector>

#include "../useful.hpp"

using namespace std;

vector<long> findPhi(long limit)
{
    vector<long> v(limit+1, 1);

    for(long n=2; n<=limit; n++)
    {
        if(v.at(n) == 1)
        {
            long m=n;

            while(m <= limit)
            {
                long e=0;
                long l = m;

                do
                {
                    l = l/n;
                    e++;
                } while(l % n == 0);

                v.at(m) *= (n-1) * power(n, e-1);

                m += n;
            }
        }
    }

    return v;
}

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
