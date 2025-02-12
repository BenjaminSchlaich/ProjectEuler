
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "triangle.hpp"

using namespace std;

Triangle parseString(const std::string& input)
{
    std::stringstream ss(input);
    std::vector<int> values;
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        values.push_back(std::stoi(token));
    }
    
    if (values.size() != 6) {
        throw std::runtime_error("Input does not contain exactly six integers.");
    }
    
    return { values[0], values[1], values[2], values[3], values[4], values[5] };
}

vector<Triangle> readFile()
{
    ifstream ifs("Problem102/0102_triangles.txt");

    if(!ifs.good())
        throw std::runtime_error("could not open input file!");

    vector<Triangle> ss;

    while(ifs.good())
    {
        string s;
        getline(ifs, s);
        ss.push_back(parseString(s));
    }

    return ss;
}

/**
 * compile: call from ProjectEuler directory:
 * clang++ -o Problem102/problem102 -std=c++2b vec.cpp Problem102/problem102.cpp
 * 
 * call: call from ProjectEuler directory:
 * ./Problem102/problem102
 */
int main()
{
    auto ts = readFile();

    bool abc = contains(ts.at(0), 0, 0);
    bool xyz = contains(ts.at(1), 0, 0);

    cout << "abc contains 0 : " << abc << endl << "xyz contains 0 : " << xyz << endl;

    int count = 0;

    for(Triangle &t: ts)
        if(contains(t, 0, 0))
            count++;

    cout << "count = " << count << endl;
}
