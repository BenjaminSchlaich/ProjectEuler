
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

using namespace std;

int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int iterate(int n)
{
    string s = to_string(n);

    int sum = 0;

    for(char c: s)
        sum += factorial[c - '0'];
    
    if(sum < 0)
        throw runtime_error("integer out of bounds: next of " + to_string(n));

    return sum;
}

struct t
{
    int next;       // next element in the sequence
    int distance;   // distance from repetition (including cycle length)
    int loopSize;   // <= distance. how large is the loop?
};

struct map
{
    // unordered_map<int, t> m;
    vector<t> v;

    map(size_t N)
    {
        // m = unordered_map<int, t>();
        v = vector<t>(N + 1);
    }

    bool isKnown(int i)
    {
        // return m.contains(i);

        if(i >= v.size())
        {
            v.resize(i+1, {-1, -1, -1});
            return false;
        }
        else
            return v.at(i).next > 0;
    }

    bool isComplete(int i)
    {
        // return isKnown(i) && m.at(i).distance > 0;
        return v.at(i).distance > 0;
    }

    void setNext(int i0, int i1)
    {
        // m.insert({i0, {i1, -1, -1}});
        v.at(i0) = {i1, -1, -1};
    }

    int getNext(int i)
    {
        // return m.at(i).next;
        return v.at(i).next;
    }

    int &getDistance(int i)
    {
        // return m.at(i).distance;
        return v.at(i).distance;
    }

    int &getLoopSize(int i)
    {
        // return m.at(i).loopSize;
        return v.at(i).loopSize;
    }
};

void find(int n, map &m)
{
    int next = n;
    int nn;
    int d = -1;

    while(!m.isKnown(next))
    {
        nn = iterate(next);
        m.setNext(next, nn);
        m.getDistance(next) = d--;
        next = nn;
    }

    int circleLength = 0;

    if(!m.isComplete(next))     // circle
    {
        circleLength = - (d - m.getDistance(next));

        do
        {
            m.getDistance(nn) = circleLength;
            m.getLoopSize(nn) = circleLength;
            nn = m.getNext(nn);
        } while(nn != next);

        d = -(d + 1);
        nn = n;
        
        while(d > circleLength)
        {
            m.getDistance(nn) = d--;
            m.getLoopSize(nn) = circleLength;
            nn = m.getNext(nn);
        }
    }
    else
    {
        circleLength = m.getLoopSize(next);
        d = -(d + 1) + m.getDistance(next);

        nn = n;

        while(nn != next)
        {
            m.getDistance(nn) = d--;
            m.getLoopSize(nn) = circleLength;
            nn = m.getNext(nn);
        }
    }
}

void solve()
{
    const int N = 999999;

    map m = map(N);

    size_t count = 0;

    for(int n=0; n<=N; n++)
    {
        find(n, m);

        if(m.getDistance(n) == 60)
            count++;
    }

    cout << "solution: " << count << endl;
}

void test()
{
    const int N = 999999;

    map m = map(N);

    size_t maxCount = 0;
    int maxN = 0;

    for(int n=0; n<=N; n++)
    {
        find(n, m);

        if(m.getDistance(n) > maxCount)
        {
            maxCount = m.getDistance(n);

            maxN = n;
        }
    }

    cout << "Maximum chain length: " << maxCount << endl;
    cout << "Maximum starting element: " << maxN << endl;
    cout << "Sequence:" << endl;

    int n = maxN;

    unordered_set<int> S;

    int i = 1;

    while(!S.contains(n))
    {
        S.insert(n);
        cout << setw(3) << (i++) << ": " << n << endl;
        n = m.getNext(n);
    }
}

int main()
{
    
    solve();

    return 0;
}
