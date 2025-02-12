
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

/*
    AB (von a zu b): a + AB - b = 0 <=> AB = b - a

    Projektion P von p=(px,py) auf v=(vx, vy): P = ß*v ; (P - p)*v = 0 <=> ß*v*v = p*v <=> ß = (p*v)/v*v
        => P = v * (p*v)/v*v
    
*/
bool contains(Triangle &t)
{
    if(t.ax != t.bx)
    {
        double m = (t.ay - t.by)/(t.ax - t.bx);
        double y0 = t.ay - t.ax*m;
    }

    
    return true;
}

int main()
{
    auto ts = readFile();

    bool abc = contains(ts.at(0));
    bool xyz = contains(ts.at(1));

    cout << "abc contains 0 : " << abc << endl << "xyz contains 0 : " << xyz << endl;
}
