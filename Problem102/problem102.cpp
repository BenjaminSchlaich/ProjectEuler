
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../vec.hpp"

using namespace std;

struct Triangle
{
    int ax, ay, bx, by, cx, cy;
};

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
    ifstream ifs("0102_triangles.txt");

    vector<Triangle> ss;

    while(ifs.good())
    {
        string s;
        getline(ifs, s);
        ss.push_back(parseString(s));
    }

    return ss;
}

bool contains(Triangle &t, int x, int y)
{
    vec p = {(double) x, (double) y};

    vec a = {(double) t.ax, (double) t.ay};
    vec b = {(double) t.bx, (double) t.bx};
    vec c = {(double) t.cx, (double) t.cy};

    return sameSide(a, b, c, p)
        && sameSide(b, c, a, p)
        && sameSide(a, c, b, p);
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
}
