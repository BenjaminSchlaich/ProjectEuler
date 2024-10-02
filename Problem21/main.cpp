
// regex to capture the right column from the table at http://www.positiveintegers.org/IntegerTables/1-100:
// ^\d+\s+\d+(?:,\s+\d+)*\s+\d+\s+\d+\s+(\d+).*$
// regex to replace the line with:
// $1

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>

long d(long n);
void basicTest();
void testSmallTable();
bool isAmicable(long n);

int main()
{
    basicTest();

    const long N = 10000;
    bool amicable[N];
    for(long i=0; i<N; i++)     // need initialization!!
        amicable[i] = false;

    for(long n=1; n<N; n++)     // check all Numbers
        if(!amicable[n])
            amicable[n] = isAmicable(n);
    
    long sum = 0;

    for(long n=1; n<N; n++)     // calculate the sum
        if(amicable[n])
        {
            sum += n;
            cout << n << " is amicable?!" << endl;
        }    

    cout << "The sum of all amicable numbers under " << N << " is " << sum << "." << endl;
    
    return 0;
}

bool isAmicable(long n)
{
    long dOfN = d(n);
    if(d(n) < 1 || d(n) == n)
        return false;

    return n == d(dOfN);
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

void basicTest()
{
    cout << "is 220 amicable? Expected true, got " << isAmicable(220) << endl;
    cout << "is 284 amicable? Expected true, got " << isAmicable(284) << endl;
}

void testSmallTable()
{
    cout << "running testFactorizeFunction()..." << endl;

    const std::string filename = "dTable.txt";
    std::ifstream ifs(filename);

    if(!ifs.good())
    {
        cout << "testFactorizeFunction(): error: could not open file " << filename << ". Abort test." << endl;
        return;
    }

    const int n = 10;
    char *line = new char[n+1];

    int i = 1;
    int failures = 0;

    while(ifs.good())
    {
        ifs.getline(line, n);
        int answer = atoi(line);
        int prediction = d(i);

        if(prediction != answer)
        {
            cout << "n = " << std::setw(2) << i << " | " << "expected " << answer << " | got " << prediction << endl;
            failures++;
        }

        i++;
    }

    if(failures > 0)
        cout << "failed test with " << failures << " errors out of " << i-1 << " cases." << endl;
    else
        cout << "passed the test with " << i-1 << " cases." << endl;

    delete[] line;
}
