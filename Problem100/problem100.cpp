
#include "../useful.hpp"

#include <iostream>
#include <cmath>

using namespace std;

long rf(long b)
{
    long double d_b = (long double) b;

    long double d_r = (1 - 2*d_b + sqrt(8*d_b*d_b - 8*d_b + 1)) / 2;

    return (long) round(d_r);
}

int main(int argc, char *argv[])
{
    long b = 707106781186;      // figuered this out using the (very good!) linear approximation of r(b) near b=10^12.
    long r = 0;
    bool found = false;

    do
    {
        r = rf(b);

        // solve the modulo equation:
        long bb = b % 123454321;
        long rr = r % 123454321;

        if(bb*bb - bb == rr*rr - (2*bb - 1)*rr)
            found = true;

    } while(!found);

    cout << "b = " << b << endl;

    return 0;
}
