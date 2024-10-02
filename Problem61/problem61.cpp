
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>

#include "../useful.hpp"

using namespace std;

typedef vector<list<int>> graph;

// these are the bounds of the sequences i determined, so that all numbers are ∈ [1000, 9999]
static const vector<pair<int, int>> bounds = {
    {0, 0},     // the start node
    {45, 140},
    {32, 99},
    {26, 81},
    {23,70},
    {21,63},
    {19,57}
};

// this is useful for running the algorithm
static bool colorUsed[7] = {false, false, false, false, false, false, false};
static list<int> path;

// maps from node id's to their numerical value, because the these are not unique (hexagonal are triangle numbers etc)
static vector<int> nodeValues = {0};

// returns the "color", i.e. the identifier of the sequence, that corresponds to a vertex id,
// to ensure that only one number is used from each sequence.
int getColor(int id);

/**
 * edges.at(v) = the list of neighbors of v
 */
bool longestPath(int v, graph &g);

graph generateGraph();

/**
 * Solution idea: run bfs with color constraints on a graph consisting of the numbers in the sequences. Runs blazingly fast.
 */
int main()
{
    graph g = generateGraph();

    cout << "Generated the graph with " << g.size() << " nodes, " << nodeValues.size() << " of which are labeled." << endl;

    if(!longestPath(0, g))
    {
        cout << "No path for a cyclic sequence was found!" << endl;
        return 0;
    }

    list<int> solution;

    for(int i: path)
        solution.push_back(nodeValues.at(i));

    cout << "The solution sequence is " << solution << endl;

    int sum = 0;

    for(int i: solution)
        sum += i;
    
    cout << "The sum of the " << solution.size() << " values is " << sum << "." << endl;

    return 0;
}

graph generateGraph()
{
    vector<function<int(int)>> fs = {
        [](int n) {return n*(n+1) / 2;},
        [](int n) {return n*n;},
        [](int n) {return n*(3*n-1) / 2;},
        [](int n) {return n*(2*n-1);},
        [](int n) {return n*(5*n-3) / 2;},
        [](int n) {return n*(3*n-2);}
    };

    // find all the nodes in the graph, i.e. the numbers in each sequence between 1000 and 9999
    for(int i=0; i<fs.size(); i++)
    {
        auto f = fs.at(i);
        int start = bounds.at(i+1).first;
        int end = bounds.at(i+1).second;

        for(int j=0; j<=end - start; j++)
            nodeValues.push_back(f(start + j));
    }

    // now we'll determine the edges and write them into an adjacency matrix
    function<bool(int, int)> isEdge = [](int n, int m) {
        string s_n = to_string(n);
        string s_m = to_string(m);
        return s_n.at(2) == s_m.at(0) && s_n.at(3) == s_m.at(1);
    };

    // initialize the adjacency lists
    graph g(nodeValues.size(), list<int>());
    
    // connect the start node (0) to all other nodes
    for(int j=1; j<nodeValues.size(); j++)
        g.at(0).push_back(j);
    
    // connect all other nodes, that need to be connected:
    for(int i=1; i<nodeValues.size(); i++)
        for(int j=1; j<nodeValues.size(); j++)
            if(i != j && isEdge(nodeValues.at(i), nodeValues.at(j)))
                g.at(i).push_back(j);
    
    return g;
}

bool longestPath(int u, graph &g)
{
    for(int v: g.at(u))
    {
        int c = getColor(v);

        if(colorUsed[c])
            continue;
        
        path.push_back(v);
        colorUsed[c] = true;

        if(path.size() == 6)
        {
            // try to find the way back to the beginning!:
            for(int w: g.at(v))
                if(path.front() == w)
                    return true;
        }
        else if(longestPath(v, g))
            return true;
        
        path.pop_back();
        colorUsed[c] = false;
    }

    return false;
}

int getColor(int id)
{   
    int color = 0;
    int upperLimit = 0;

    while(color <= 6)
    {
        upperLimit += bounds.at(color).second - bounds.at(color).first + 1;

        if(id < upperLimit)
            return color;
        
        color++;
    }
    
    throw runtime_error("getColor(): argument >" + to_string(id) + "< not identifiable, out of range!");
}
