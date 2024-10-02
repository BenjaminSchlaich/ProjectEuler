
#define CACHING false

#include <vector>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>

#include <cmath>

#include <chrono>

typedef std::vector<double> vector;

static const double INF = std::numeric_limits<double>::infinity();

static vector allNegCache;
static std::vector<vector> allNeg1Cache;

double solve(double p, int N);

inline double allNegative(double k, double p);

inline double allNegative1(double k, double n, double p);

void runProblem();

void runTest();

void testRuntime();

void initCache(size_t size);

int main()
{
    runProblem();

    return 0;
}

inline double allNegative(double k, double p)
{
    #if CACHING

    if(allNegCache.at(k) == -1)
    {
        allNegCache.at(k) = pow(1 - p, k);
        return allNegCache.at(k);
    }
    else
        return allNegCache.at(k);
    
    #else   // CACHING

    return pow(1 - p, k);

    #endif  // CACHING
}

inline double allNegative1(double k, double n, double p)
{
    #if CACHING

    if(allNeg1Cache.at(k).at(n) != -1)
        return allNeg1Cache.at(k).at(n);

    // let A: "WLOG the first k out of n sheep are negative"
    // let B: "at least one of the n sheep is positive"
    // using bayes formula: P[ A | B ] = P[A ∩ B] / P[ B ]:
    // P[A ∩ B] = (1-p)^k * (1 - (1-p)^(n-k))
    // P[ B ] = 1 - (1-p)^n
    double pAandB = pow(1 - p, k) * (1 - pow(1 - p, n - k));
    double pB = 1 - pow(1 - p, n);

    allNeg1Cache.at(k).at(n) = pAandB / pB;

    return allNeg1Cache.at(k).at(n);

    #else   // CACHING

    double pAandB = pow(1 - p, k) * (1 - pow(1 - p, n - k));
    double pB = 1 - pow(1 - p, n);
    return pAandB / pB;

    #endif  // CACHING
}

void runTest()
{
    cout << "running runTest()..." << endl;

    double answer = solve(0.02, 25);

    cout << "N = 25, p = 0.02: expected 4.155452, got " << answer << "." << endl;

    answer = solve(0.1, 25);

    cout << "N = 25, p = 0.10: expected 12.702124, got " << answer << "." << endl;
}

void runProblem()
{
    double sum = 0;
    int N = 10000;

    for(double p=0.01; p < 0.501; p+=0.01)
    {
        cout << "now solving for p = " << std::setw(5) << p;

        auto t0 = std::chrono::high_resolution_clock::now();

        double s = solve(p, N);

        auto t1 = std::chrono::high_resolution_clock::now();

        int d = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        sum += s;
        cout << " | " << std::setw(7) << s << " | duration: " << std::setw(6) << d << "ms" << endl;
    }

    std::cout << std::setprecision(20);
    cout << "The sum of it all: " << sum << endl;
}

void testRuntime()
{
    std::chrono::duration<long, std::milli> milliExec;
    int N = 100;

    do
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        solve(0.02, N);

        auto t1 = std::chrono::high_resolution_clock::now();

        milliExec = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

        cout << "N = " << std::setw(5) << N << " | " << milliExec.count() << endl;

        N *= 2;
    } while (milliExec.count() < 20000);
    
}

double solve(double p, int N)
{
    // dp.at(i) := average number of tests needed to test i sheep
    vector dp(N+1);
    dp.at(0) = 0;
    dp.at(1) = 1;

    vector dp1(N+1);
    dp1.at(0) = 0;
    dp1.at(1) = 0;

    initCache(N+1);

    for(int i=2; i<=N; i++)         // i is the number of all sheep to be tested => dp.at(i) for i==N is the solution
    {
        double min0 = INF;
        double min1 = INF;

        // how did i come up with 200 as a threshold for the group size?
        // Guessed upper bound, for when it never makes sense to test a larger group:
        // when the probability for the group being positive t >= 0.99
        // => P["not all j negative"] <= t <=> 1 - (1-p)^g <= t <=> g <= log(1-p, 1-t) => g <= 228
        for(int j = 1; j<std::min(i, 228); j++)    // find the best group size for testing the next subgroup
        {
            // if we do not know, whether any sheep is positive, the following holds:
            // we test our group of j ("1 + ..."),
            // if the test is positive ("... 1 - allNegative(j, p)...")
            // we must look at the expected value of tests for j sheep, where at least one is positive ("dp1.at(j)"),
            // and independent of the test, we test the rest of the group ("dp.at(i-j)")
            double curr0 = 1 + (1 - allNegative(j, p)) * dp1.at(j) + dp.at(i - j);

            // if we do know, that at least one sheep is positive, the method is similar, but not the same:
            // first we test our group of j ("1 + ..."),
            // if the test is positive ("... 1 - allNegative1(j, i, p)..."), where we know, that one of all i is positive
            // we must test inside our group, as well as the rest ("dp1.at(j) + dp.at(i-j)"), where only in our group we know, that one must be positive
            // and, if the test is negative ("allNegative1(j, i, p)"), then we know, that the positive one from the previous test
            // is in the rest (i-j), so we test inside the rest group ("dp1.at(i - j)").
            double curr1 = 1 + (1 - allNegative1(j, i, p)) * (dp1.at(j) + dp.at(i-j)) + allNegative1(j, i, p) * dp1.at(i - j);

            min0 = std::min(min0, curr0);
            min1 = std::min(min1, curr1);

            if(i == 25)
            {
                //cout << "j = " << std::setw(3) << j << ", curr0 = " << std::setw(8) << curr0 << ", curr1 = " << curr1 << endl;
                // cout << "j = " << std::setw(3) << j << ", options: " << std::setw(8) << curr0 << " | " << 1 + (1 - allNegative(i, p)) * curr1 << endl;
            }
        }
        
        // either start testing the group, or test all first, and then, if necessary, the group
        dp.at(i) = std::min(min0, 1 + (1 - allNegative(i, p)) * min1);
        dp1.at(i) = min1;
    }

    return dp.at(N);
}

void initCache(size_t size)
{
    allNegCache.resize(size);
    allNeg1Cache.resize(size);
    for(size_t i=0; i<size; i++)
        allNeg1Cache.at(i).resize(size);

    std::fill(allNegCache.begin(), allNegCache.end(), -1);
    for(size_t i=0; i<size; i++)
        std::fill(allNeg1Cache.at(i).begin(), allNeg1Cache.at(i).end(), -1);
}
