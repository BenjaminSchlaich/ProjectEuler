
#include "triangle.hpp"

#include <string>
#include <fstream>
#include <random>

using namespace std;

void generateTests(int bound = 5, int samples = 10, string filename = "Problem102/test_data/tr")
{
    mt19937_64 prng(547438);
    uniform_int_distribution dist(-bound, bound);

    for(int i=0; i<samples; i++)
    {
        ofstream ofs(filename + to_string(i) + ".txt");

        // generate one sample and print it
        for(int j=0; j<6; j++)
        {
            ofs << dist(prng);
            
            if(j % 2 == 0)
                ofs << ", ";
            else
                ofs << endl;
        }

        ofs.close();
    }
}

/**
 * compile:
 * clang++ -o Problem102/randomTests -std=c++2b vec.cpp Problem102/triangle.cpp Problem102/randomTests.cpp
 * 
 * run:
 * 
 */
int main()
{
    generateTests();
}
