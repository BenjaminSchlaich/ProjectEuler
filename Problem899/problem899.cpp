
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
 * Returns, whether the first player can win this scenario, assuming perfect play.
 * -1 = looses
 * 1 = wins with perfect play
 */
int solve_one(int a, int b)
{
    assert(a > 0 && b > 0);

    if(a == b)
        return -1;

    int x = a < b ? a : b;
    int y = a >= b ? a : b;

    if(x == 1)
        if(y % 2 == 0)
            return 1;
        else
            return -1;
    else if(y % 4 == 3)
        return -1;
    else
        return 1;
}

/**
 *  x 1 2 3 4 5 6 7 8 9 10 11
 * y
 * 1  l w l w l w l w l  w  l
 * 2    l l w w w l w w  w  l
 * 3      l w w w l w w  w  l
 * 4        l w w l w w  w  l
 * 5          l w l w w  w  l
 * 6            l l w w  w  l
 * 7              l w w  w  l
 * 8                l w  w  l
 * 9                  l  w  l
 * 10                    l  l
 * 11                       l
 */

/**
 * build:
 * flg="-std=c++2b -o problem899 -fsanitize=address -Wall -Werror"
 * src="problem899.cpp"
 * build="clang++ $flg $src"
 * eval $build
 * 
 * run:
 * ./problem899
 */
int main()
{
    const int n = 7;
    int sum = 0;

    for(int b=1; b<=n; b++)
        for(int a=1; a<=n; a++)
            if(solve_one(a, b) < 0)
                sum++;
    
    cout << "The number of ordered pairs (a, b), s.t. 1 <= a <= b <= " << n << ", where the first player looses is " << sum << "." << endl;
}
