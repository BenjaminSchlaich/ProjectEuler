
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

static vector<int> p = vector<int>();
static int nextI = 0;
static unordered_map<int, int> ind = unordered_map<int, int>();

// takes an index (starting at 1) and returns the <index>-th pentagonal number
int getP(int index)
{
    if(index < nextI)
        return p.at(index);
    
    while(index >= nextI)
    {
        int pp = nextI*(3*nextI - 1) / 2;

        p.push_back(pp);

        ind.insert({pp, nextI});

        nextI++;
    }

    return p.back();
}

bool isP(int pp)
{
    if(ind.contains(pp))
        return true;

    while(p.back() < pp)
    {
        int pp = nextI*(3*nextI - 1) / 2;

        p.push_back(pp);

        ind.insert({pp, nextI});

        nextI++;
    }

    return p.back() == pp;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "call like this: " << "./main <maximum index for search>" << endl;
        return 0;
    }

    int i = 0;
    // int IMAX = atoi(argv[1]);

    int IMAX = 2167;

    while(i <= IMAX)
    {
        int pi = getP(i);

        for(int j=i-1; j>0; j--)
        {
            int pj = getP(j);
            
            if(isP(pi - pj) && isP(pi + pj))
            {
                cout << "p(" << i << ") = " << pi << ", " << "p(" << j << ") = " << pj << endl;
                cout << "p(i) - p(j) = " << pi - pj << endl;

                return 0;
            }
        }

        i++;
    }

    cout << "No such number found up to p(" << i - 1 << ") = " << p.back() << endl;
}
