
#include <iostream>
#include <cmath>

using namespace std;

int getP(int i)
{
    return i*(3*i - 1) / 2;
}

bool isP(int p)
{
    int i = round((0.5 + sqrt(0.25 + 6*p)) / 3);

    return getP(i) == p;
}

int main()
{
    int i = 0;
    int IMAX = 2167;

    while(i <= IMAX)
    {
        int pi = getP(i);

        for(int j=i-1; j>0; j--)
        {
            int pj = getP(j);
            
            if(isP(pi - pj) && isP(pi + pj))
            {
                cout << "p(" << i << ") = " << pi << ", " << "p(" << j << ") = " << pj << endl;
                cout << "p(i) - p(j) = " << pi - pj << endl;

                return 0;
            }
        }

        i++;
    }

    cout << "No such number found up to p(" << i - 1 << ") = " << getP(i - 1) << endl;
}
