
#include <iostream>
using std::cout;
using std::endl;

long d(long n);
void basicTest();

int main()
{
    const int N = 28123;
    bool abundant[N+1];

    cout << "Precomputing values d(n) for 1 to " << N << "..." << endl;

    for(long i=1; i<=N; i++)
        abundant[i] = d(i) > i;
    
    cout << "Precomputation done. Now finding solution..." << endl;

    long sum = 0;

    for(long i=1; i<=N; i++)
    {
        bool foundSum = false;

        for(long j=1; j<i; j++)
            if(abundant[j] && abundant[i - j])
            {
                foundSum = true;
                break;
            }
        
        if(!foundSum)
            sum += i;
    }

    cout << "The solution is " << sum << "." << endl;

    return 0;
}

long d(long n)
{
    if(n == 1)
        return 0;

    long factor = 2;    // start search at 2
    long sum = 1;       // 1 is always a factor

    while(factor*factor < n)            // no factor can be >= than sqrt(n), because it's pair has been counted already.
    {
        if(n % factor == 0)
            sum += factor + n/factor;   // count the factor pair for better runtime.
        
        factor++;
    }

    if(factor*factor == n)
        sum += factor;                  // special case: this must be counted only once!

    return sum;
}
