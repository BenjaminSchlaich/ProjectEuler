
#include <iostream>
using std::cout, std::endl;

#include <fstream>

#include <algorithm>

#include <vector>

#include <string>
using std::string;

static const string inputFileName = "0022_names.txt";

std::vector<string> *readInputFile();

long alphaValue(string &s);

int main()
{
    auto v = readInputFile();

    cout << "Retrieved " << v->size() << " names as input. Now sorting them..." << endl;

    std::sort(v->begin(), v->end());

    cout << "Done sorting. Calculating sum of products..." << endl;

    cout << "Name at 938-th position: " << v->at(937) << endl;

    cout << "Alphabetical value of that name: " << alphaValue(v->at(937)) << endl;

    long sum = 0;

    for(int i=0; i<v->size(); i++)
        sum += (i+1) * alphaValue(v->at(i));

    cout << "Total sum of weighted alphabetical values: " << sum << endl;

    return 0;
}

long alphaValue(string &s)
{
    long sum = 0;

    for(char c: s)
        sum += c - 'A' + 1;
    
    return sum;
}

std::vector<string> *readInputFile()
{
    cout << "running readInputFile()..." << endl;

    std::ifstream ifs(inputFileName);

    if(!ifs.good())
    {
        cout << "testFactorizeFunction(): error: could not open file " << inputFileName << ". Abort test." << endl;
        return nullptr;
    }

    string line;
    std::vector<string> *v = new std::vector<string>();

    while(ifs.good())
    {
        std::getline(ifs, line, ',');

        v->push_back(line.substr(1, line.size()-2));    // cut off the quotes
    }

    return v;
}
