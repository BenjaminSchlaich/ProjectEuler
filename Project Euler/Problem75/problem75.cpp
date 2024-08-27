
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

long getRuntime(size_t N)
{
    size_t i = 1;

    size_t count = 0;

    auto t0 = chrono::high_resolution_clock::now();

    while(i*i <= N)
    {
        for(size_t j=1; j<=i; j++)
            count++;
        
        i++;
    }
    
    auto t1 = chrono::high_resolution_clock::now();

    cout << "checksum: " << count << endl;

    return chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
}

void recordRuntimes()
{
    string filename = "Problem75/runtimes.txt";

    ofstream ofs(filename);

    if(!ofs.good())
        throw runtime_error("Could not open file " + filename + ".");

    size_t stepSize = 1000000000;

    for(size_t N = stepSize; N<=10*stepSize; N+=stepSize)
    {
        double t = getRuntime(N);

        ofs << N << " " << t << endl;
    }
}

int main()
{
    recordRuntimes();

    return 0;
}
