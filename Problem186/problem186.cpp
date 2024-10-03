
#include <iostream>
#include <vector>
#include <list>

using namespace std;

static int s[55];                       // s[(k-1) % 55] contains S(k).
static const int N = 1000000;           // the modulus and number of people.
static const int PM = 524287;           // Prime Minister's number.
static vector<list<int>> g(N);          // this is just the graph as an adjacency list.
static vector<bool> isFriend(N);        // this attribute should change our speed vastly!

int getS(int k)
{             
    k--;    // use 0-54 instead of 1-55.

    if(k < 55)                                                         
    {          
        int kk = k+1;

        int a = (200003 * kk) % 1000000;
        int b = (300007 * kk) % 1000000;
        b = (b * kk) % 1000000;
        b = (b * kk) % 1000000;

        s[k] = (100003 - a + b) % 1000000;

        if(s[k] < 0)
            s[k] = 1000000 + s[k];

        if(kk < 7)
            cout << "S_" << k << " = " << s[k] << endl;
        
        return s[k];
    }
    else                                                                
    {
        s[k % 55] = (s[(k - 24) % 55] + s[k % 55]) % 1000000;               // (k - 55) % 55 == k % 55
        return s[k % 55];
    }
}

void init()
{
    for(int k=0; k<1000000; k++)
    {
        g[k] = {};
        isFriend[k] = false;
    }

    isFriend[PM] = true;
}

// recursion here gave me a stack overflow, so now using bfs with queue instead.
int closeFriends0(int u)
{
    if(isFriend[u])
        return 0;
    
    isFriend[u] = true;
    int newFriends = 1;

    for(int v: g.at(u))
        newFriends += closeFriends0(v);
    
    // this part of the graph isn't needed any longer:
    g[u].clear();

    return newFriends;
}

int closeFriends(int u)
{
    if(isFriend[u])
        return 0;
    
    isFriend[u] = true;
    int newFriends = 1;

    list<int> l = {u};

    while(!l.empty())
    {
        u = l.front();
        l.pop_front();

        for(int v: g[u])
            if(!isFriend[v])
            {
                isFriend[v] = true;
                newFriends++;
                l.push_back(v);
            }
        
        g[u].clear();   // these will never be needed again!
    }

    return newFriends;
}

int solve()
{
    init();

    /**
     * Here is my idea:
     * The algorithm is pretty naive, by just building a adjacency list for each node, and if an edge
     * that is added contains the P.M.'s number, a search through that graph is started to add the transitive closure.
     * But: Since we also store an entry isFriend for each node, we can abort the search, if isFriend is true.
     * This will be the case espacially if the graph gets very connected towards the end, so instead of more and more expensive
     * graph traversal's, we will actually have to do no additional work! In fact, every subtree will be visited only once.
     * In order to illustrate this, consider the following: towards the end, when nearly 99% of nodes are connected to the P.M.,
     * for nearly all edges that we still encounter, there is no need to traverse anything, since we have a 99% chance (if we suppose
     * that S is roughly uniformly random) that isFriend is already true. Note, that there is no need to search the subtree,
     * since the edges of the connected nodes further in the search tree could not have changed, as we repeat this
     * search for every edge that we add.
     * Question: Will we not have to search through S during longer and longer periods without finding a new Friend?
     * I do think so, but we have to generate S until we reach that point anyways (computing a sufficient bound of elements in S is
     * definitely a lower bound to the problem), and can do so pretty efficiently (just 56 array entries and simple add/mult ops).
     */

    /**
     * Additional speedup idea:
     * Track the nodes connected through edges that were added after the last friend was found.
     * Only these nodes need to be checked, and if we search them when the next friend is found,
     * we never have to search through all edges with isFriend == false when connecting a new edge.
     * This should be much more efficient yet.
     * Tracking connected components like this should be easy using a union-bound data structure,
     * comparable to the one used in Boruvka's MST algorithm.
     * In this case, we don't even have to track the whole graph g as above, but only the connected components.
     * This is obviously smarter, as ultimatly the task is equivalent to the following formulation:
     * "Find the minimum nummber k, such that after inserting the edges S1, ..., Sk, the connected component
     * that contains P.M., also contains >=99% of all nodes."
     */

    int friendCount = 1;

    int n = 0;

    while(friendCount < 990000)
    {
        int n1 = getS(++n);
        int n2 = getS(++n);

        if(n1 == n2)
            continue;
        else if(n1 == PM || n2 == PM)
            cout << "P.M. found after " << n/2 << " edges." << endl;
        
        g[n1].push_back(n2);
        g[n2].push_back(n1);

        if(isFriend[n1])
            friendCount += closeFriends(n2);
        else if(isFriend[n2])
            friendCount += closeFriends(n1);
    }

    return n/2;
}

/**
 * compile:
 * clang++ -std=c++20 -Wall -Werror -ferror-limit=1 -o Problem186/problem186 Problem186/problem186.cpp
 */
int main()
{
    cout << "solving problem 186." << endl;

    int solution = solve();

    cout << "solution: " << solution << endl;
}
