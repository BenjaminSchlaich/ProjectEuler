
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cache = vector<int>();
int cacheMaxI = 0;
int cacheMax = 0;

int p(int n)
{
    return n * (3*n - 1) / 2;
}

bool isPentagonal(int n)
{
    if(n > cacheMax)
    {
        while(n > cacheMax)
        {
            cacheMaxI++;
            cacheMax = p(cacheMaxI);
            cache.push_back(cacheMax);
        }

        return n == cacheMax;
    }
    else
    {
        return binary_search(cache.begin(), cache.end(), n);
    } 
}

int main()
{
    int j = 1;
    int k = 1;
    int pj;
    int pk;
    bool found = false;

    do
    {
        pj = p(j);

        for(k = 1; k<j; k++)
        {
            pk = p(k);
            
            if(isPentagonal(pj - pk))
            {
                found = true;
                break;
            }
        }

    } while (!found);
    
    cout << "j = " << j << ", pj = " << pj << ", k = " << k << ", pk = " << pk << ", D = " << pj - pk << endl;
    
    return 0;
}
