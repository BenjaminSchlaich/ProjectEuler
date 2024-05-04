
#include <iostream>

using namespace std;

static const long START = 1;

long hexagonal(long i)
{
    return i * (2*i - 1);
}

bool isPentagonal(long n)
{
    long i = round((0.5 + sqrt(0.25 + 6*n)) / 3);
    long p = i * (3 * i - 1) / 2;

    return p == n;
}

bool isTriangle(long n)
{
    long i = sqrt(0.25 + 2 * n) - 0.5;

    long t = i * (i + 1) / 2;

    return t == n;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "call like this: ./problem45 <maximum search index>" << endl;
        return 0;
    }

    long MAXI = atol(argv[1]);

    for(long i = START; i<=MAXI; i++)
    {
        long h = hexagonal(i);

        if(isTriangle(h) && isPentagonal(h))
            cout << "found a number that is triangle, pentagonal and hexagonal: " << h << endl;
    }

    cout << "counted from index " << START << " to " << MAXI << endl;

    return 0;
}
