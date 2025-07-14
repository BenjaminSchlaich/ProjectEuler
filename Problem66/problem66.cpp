
#include <iostream>
#include <vector>

using namespace std;
/*
static long lastI = 0;
static vector<bool> squareSieve = {true};

bool isSquare(long i)
{
    while(squareSieve.size() <= i)
    {
        lastI++;
        
        while(squareSieve.size() < lastI*lastI)
            squareSieve.push_back(false);
        
        squareSieve.push_back(true);
    }

    return squareSieve.at(i);
}
/*/

bool isSquare(const long i)
{
    for(long j=0; j*j<=i; j++)
        if(j*j == i)
            return true;
    
    return false;
}

/**
 * 
 * x^2 - 61*y^2 = 1
 * 
 * sqrt(61*y^2 + 1)
 * 
*/

//*/
/**
 *      x^2 - D*y^2 = 1
 * <=>  x^2 - 1     = D*y^2
 */
bool satisfies(long x, long D)
{
    long x2m1 = x*x - 1;

    if(x2m1 % D != 0)
        return false;
    
    long y2 = x2m1 / D;

    return isSquare(y2);
}

long findMinX(long D)
{
    long x = 2;

    while(!satisfies(x, D))
        x++;
    
    return x;
}

/**
 *      x^2 - D*y^2 = 1
 * <=>  x^2 = 1 + D*y^2
 * <=>  x = sqrt( 1 + D*y^2 )
 */
long findMinX2(long D)
{
    for(long y=1; ; y++)
    {
        if(isSquare(1 + D*y*y))
        {
            return (long) round(sqrt(1 + D*y*y));
        }
    }

    return 0;
}

long findBestD(bool verbose = false)
{
    long bestD = 0;
    long largestMinX = 0;

    for(long D=1; D<=1000; D++)
    {
        if(isSquare(D))
            continue;
        
        cout << "D = " << D << endl;
        
        long minX = findMinX2(D);

        if(minX > largestMinX)
        {
            bestD = D;
            largestMinX = minX;

            // cout << "found new optimum: D = " << D << " -> minimum x = " << minX << endl;
        }
    }

    return bestD;
}

void testFunction()
{
    for(long d=2; d<=7; d++)
    {
        if(isSquare(d))
            continue;
        
        cout << findMinX(d) << "^2 - " << d << " * y^2 = 1" << endl;
    }
}

/**
 * compile:
 * clang++ -std=c++2b -Werror -Wall -ferror-limit=1 -o Problem66/problem66 Problem66/problem66.cpp
 */
int main()
{
    cout << "precomputing a large square check..." << endl;

    long testSquare = 100*1000*1000;
    cout << "isSquare(" << testSquare << ") = " << isSquare(testSquare) << endl;

    cout << "Now the solution finding process may start..." << endl;

    // cout << "min x for D = 13 : " << findMinX(13) << endl;

    // testFunction();

    findBestD(true);

    return 0;
}
