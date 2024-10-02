
#include <iostream>
#include <unordered_set>
#include <list>

using namespace std;

static const int L = 4;

// print a set of integers
std::ostream &operator<<(std::ostream &os, std::unordered_set<int> S);

// returns all prime factors of n
std::unordered_set<int> factors(int n);

int main(int argc, char *argv[])
{
    list<unordered_set<int>> sets;

    for(int i=1; i<=L; i++)
        sets.push_back(factors(i));

    int n = L;

    do
    {
        bool allFit = true;

        for(auto s: sets)
            if(s.size() != L)
            {
                allFit = false;
                break;
            }
        
        if(allFit)
        {
            cout << n - L + 1 << endl;
            return 0;
        }

        sets.push_back(factors(++n));
        sets.pop_front();

    } while(true);
}

std::unordered_set<int> factors(int n)
{
    std::unordered_set<int> S;

    // treat 2 as a special case
    if(n % 2 == 0)  // 2 is a prime factor of n
    {
        S.insert(2);
        
        do n /= 2; while(n % 2 == 0);
    }

    int f = 3;

    while(n > 1)
    {
        if(n % f == 0)  // f is a prime factor of n
        {
            S.insert(f);

            do n /= f; while(n % f == 0);
        }

        f += 2;
    }

    return S;
}

std::ostream &operator<<(std::ostream &os, std::unordered_set<int> S)
{
    os << "[";

    auto it = S.begin();

    if(it != S.end())
        os << *it++;
    
    while(it != S.end())
        os << " ," << *it++;
    
    os << "]";

    return os;
}
