
/**
 * COMPILE: clang++ -std=c++20 -o main -O2 main.cpp
 * RUN:     ./main
*/

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>

#include <iomanip>

#include <vector>
#include <utility>

typedef std::vector<std::pair<int, int>> factorization;

int factorize(long n, factorization &f);

// returns the number of divisors of A*B, where fA is the prime factorization of A, and fB of B.
int numberOfDivisors(factorization &fA, factorization &fB);

long solve(long divs);

void runProblem();

void runTest();

/**
 * Compares the results to the wikipedia table up to 30
*/
void testFactorizeFunction();

/**
 * Compare to a couple of hand-made test cases.
*/
void testNumberOfDivisors();

int main()
{
    testFactorizeFunction();

    cout << endl;

    testNumberOfDivisors();

    cout << endl;

    runTest();

    cout << endl;

    runProblem();

    return 0;
}

int factorize(long n, factorization &f)
{
    long factor = 3;
    int divisors = 1;
    int primeExp = 0;

    f.clear();

    // get this out first for speedup!
    while(n % 2 == 0)
    {
        n /= 2;
        primeExp++;
    }

    if(primeExp > 0)
        f.push_back(std::make_pair(2, primeExp));

    divisors *= primeExp + 1;

    while(n > 1)
    {
        primeExp = 0;

        while(n % factor == 0)
        {
            n /= factor;
            primeExp++;
        }

        if(primeExp > 0)
            f.push_back(std::make_pair(factor, primeExp));

        divisors *= primeExp + 1;
        primeExp = 0;

        factor += 2;
    }

    return divisors;
}

int numberOfDivisors(factorization &fA, factorization &fB)
{
    int divs = 1;

    size_t i1 = 0;
    size_t i2 = 0;

    while(i1 < fA.size() || i2 < fB.size())
    {
        while(i1 < fA.size() && (i2 >= fB.size() || fA.at(i1).first < fB.at(i2).first))   // non-shared prime factors of n
        {
            divs *= fA.at(i1).second + 1;
            i1++;
        }
        
        while(i2 < fB.size() && (i1 >= fA.size() || fB.at(i2).first < fA.at(i1).first))   // non-shared prime factors of (n + 1)
        {
            divs *= fB.at(i2).second + 1;
            i2++;
        }

        if(i1 < fA.size() && i2 < fB.size() && fA.at(i1).first == fB.at(i2).first)
        {
            divs *= fA.at(i1).second + fB.at(i2).second + 1;
            i1++;
            i2++;
        }
    }

    return divs;
}

long solve(long divs)
{
    long n = 1;
    int divisors = 1;

    factorization f = {};
    factorization cached;

    int currMax = 0;

    do
    {
        n++;
        cached = f;

        if(n % 2 == 0)          // make sure we compute n*(n+1)/2, not just n*(n+1).
            factorize(n/2, f);
        else
            factorize(n, f);
        
        divisors = numberOfDivisors(f, cached);

        if(currMax < divisors)
            cout << "current maximum at " << currMax << endl;
        
        currMax = std::max(currMax, divisors);

    } while(divisors <= divs);

    return n*(n-1)/2;
}

void runProblem()
{
    cout << "running runProblem()..." << endl;

    long divs = 500;
    long solution = solve(divs);

    cout << "result: " << solution << endl;
}

void runTest()
{
    cout << "running runTest()..." << endl;

    long divs = 5;
    long solution = solve(divs);

    cout << "Expected 28, got " << solution << endl;
}

void testFactorizeFunction()
{
    cout << "running testFactorizeFunction()..." << endl;

    const std::string filename = "divisorsTable.txt";
    std::ifstream ifs(filename);

    if(!ifs.good())
    {
        cout << "testFactorizeFunction(): error: could not open file " << filename << ". Abort test." << endl;
        return;
    }

    const int n = 10;
    char *line = new char[n+1];
    factorization f;

    int i = 1;
    int failures = 0;

    while(ifs.good())
    {
        ifs.getline(line, n);
        int answer = atoi(line);
        int prediction = factorize(i, f);

        if(prediction != answer)
        {
            cout << "n = " << std::setw(2) << i << " | " << "expected " << answer << " | got " << prediction << endl;
            failures++;
        }

        i++;
    }

    if(failures > 0)
        cout << "failed test with " << failures << " errors." << endl;
    else
        cout << "passed the test." << endl;

    delete[] line;
}

void testNumberOfDivisors()
{
    cout << "running testFactorizeFunction()..." << endl;

    const int inA[] = {6, 8, 12};
    const int inB[] = {6, 10, 4};
    const int answer[] = {9, 10, 10}; // 36->9, 80->10, 48->10

    int T = sizeof(inA) / sizeof(int);

    cout << "running " << T << " test cases." << endl;

    factorization fA;
    factorization fB;

    int failures = 0;

    for(int t=0; t<T; t++)
    {
        factorize(inA[t], fA);
        factorize(inB[t], fB);

        int prediction = numberOfDivisors(fA, fB);

        if(prediction != answer[t])
        {
            cout << "n = " << std::setw(2) << inA[t]*inB[t] << " | " << "expected " << answer << " | got " << prediction << endl;
            failures++;
        }
    }

    if(failures > 0)
        cout << "failed test with " << failures << " errors." << endl;
    else
        cout << "passed the test." << endl;
}
