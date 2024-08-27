
#include <iostream>
#include <vector>

using namespace std;

const int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

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

struct map
{
    vector<pair<int, int>> v;

    map(size_t N)
    {
        v = vector<pair<int, int>>(N + 1);
    }

    bool isKnown(int i)
    {
        if(i >= v.size())
        {
            v.resize(i+1, {-1, -1});
            return false;
        }
        else
            return v.at(i).first > 0;
    }

    bool isComplete(int i)
    {
        return v.at(i).second > 0;
    }

    void setNext(int i0, int i1)
    {
        v.at(i0) = {i1, -1};
    }

    int getNext(int i)
    {
        return v.at(i).first;
    }

    int &getDistance(int i)
    {
        return v.at(i).second;
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

    if(!m.isComplete(next))
    {
        circleLength = - (d - m.getDistance(next));

        do
        {
            m.getDistance(nn) = circleLength;
            nn = m.getNext(nn);
        } while(nn != next);

        d = -(d + 1);
        nn = n;
        
        while(d > circleLength)
        {
            m.getDistance(nn) = d--;
            nn = m.getNext(nn);
        }
    }
    else
    {
        d = -(d + 1) + m.getDistance(next);

        nn = n;

        while(nn != next)
        {
            m.getDistance(nn) = d--;
            nn = m.getNext(nn);
        }
    }
}

int main()
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
