
#include <list>
#include <vector>
#include <functional>
#include <iostream>

#include "../useful.hpp"

using namespace std;

/**
 * edges.at(v) = the list of neighbors of v
 */
list<int> longestPath(int v, vector<list<int>> &edges, int depth);

static vector<int> nodeValues = {0};

// true <=> the last two digits of u are the first two of v
bool isEdge(int u, int v);

vector<list<int>> generateGraph();

int main()
{
    vector<list<int>> g = generateGraph();

    list<int> solution = longestPath(0, g, 7);

    for(int &i: solution)
        i = nodeValues.at(i);

    cout << "The solution sequence is " << solution << endl;

    int sum = 0;

    for(int i: solution)
        sum += i;
    
    cout << "The sum of the " << solution.size() << " values is " << sum << "." << endl;

    return 0;
}

vector<list<int>> generateGraph()
{
    vector<list<int>> g;

    vector<function<int(int)>> fs = {
        [](int n) {return n*(n+1) / 2;},
        [](int n) {return n*n;},
        [](int n) {return n*(3*n-1) / 2;},
        [](int n) {return n*(2*n-1);},
        [](int n) {return n*(5*n-3) / 2;},
        [](int n) {return n*(3*n-2);}
    };

    vector<pair<int, int>> bounds = {
        {45, 140},
        {32, 99},
        {26, 81},
        {23,70},
        {21,63},
        {19,57}
    };

    function<bool(int, int)> isEdge = [](int n, int m) {
        string s_n = to_string(n);
        string s_m = to_string(m);
        return s_n.at(2) == s_m.at(0) && s_n.at(3) == s_m.at(1);
    };

    list<int> startEdges;

    for(int i=1; i<=bounds.at(0).second - bounds.at(0).first + 1; i++)
        startEdges.push_back(i);
    
    g.push_back(startEdges);

    vector<int> startIDs = {1};

    for(int i=0; i<bounds.size(); i++)
        startIDs.push_back(startIDs.at(i) + bounds.at(i).second - bounds.at(i).first + 1);

    for(int l=0; l<6; l++)
    {
        int ll = (l+1) % 6;

        for(int n=bounds.at(l).first; n<=bounds.at(l).second; n++)
        {
            int u = fs.at(l)(n);

            nodeValues.push_back(u);
            g.push_back(list<int>());

            for(int m=bounds.at(ll).first; m<=bounds.at(ll).second; m++)
            {
                int v = fs.at(ll)(m);

                if(isEdge(u, v))
                {
                    int vid = startIDs.at(ll) + m - bounds.at(ll).first;

                    g.back().push_back(vid);
                }
            }
        }
    }

    return g;
}

list<int> longestPath(int v, vector<list<int>> &edges, int depth)
{
    list<int> lMax;

    if(depth == 0)
        return lMax;

    for(int u: edges.at(v))
    {
        list<int> uPath = longestPath(u, edges, depth - 1);
        
        uPath.push_front(u);

        if(uPath.size() > lMax.size())
            lMax = uPath;
    }

    return lMax;
}
