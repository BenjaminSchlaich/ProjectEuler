
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
bool contains(Triangle &t, int x, int y)
{
    // (x,y) on one side with C from AB:
    int abx = t.bx - t.ax;
    int aby = t.by - t.ay;

    int cSide = abx*t.cx + aby*t.cy <= 0 ? -1 : 1;
    int pSide = abx*x + aby*y <= 0 ? -1 : 1;

    if(cSide != pSide)
        return false;

    // (x,y) on one side with B from AC:
    int acx = t.cx - t.ax;
    int acy = t.cy - t.ay;

    int bSide = acx*t.bx + acy*t.by <= 0 ? -1 : 1;
    pSide = acx*x + acy*y <= 0 ? -1 : 1;

    if(bSide != pSide)
        return false;
    
    // (x,y) on one side with A from BC:
    int bcx = t.cx - t.bx;
    int bcy = t.cy - t.by;

    int aSide = bcx*t.ax + bcy*t.ay <= 0 ? -1 : 1;
    pSide = bcx*x + bcy*y <= 0 ? -1 : 1;

    if(aSide != pSide)
        return false;
    
    return true;
}

int main()
{
    auto ts = readFile();

    bool abc = contains(ts.at(0), 0, 0);
    bool xyz = contains(ts.at(1), 0, 0);

    cout << "abc contains 0 : " << abc << endl << "xyz contains 0 : " << xyz << endl;
}
