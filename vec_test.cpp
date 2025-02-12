
#include "vec.hpp"

#include <iostream>
#include <vector>

using namespace std;

/**
 * Visualization of the test sets:
 * 
 *    v1              v2
 *      *           *
 *        *  D2   *
 *          *   *
 *       D3   *   D1
 *          *   *
 *        *  D4   *
 *      *           *
 */
static vector<vec> D1 = vector<vec>({{1, 0}, {2, 1}, {3, 1}, {3, 2}, {2, -1}, {3, -1}, {3, -2}});
static vector<vec> D2 = vector<vec>({{0, 1}, {1, 2}, {1, 3}, {2, 3}, {-1, 2}, {-1, 3}, {-2, 3}});
static vector<vec> D3 = vector<vec>({{-1, 0}, {-2, 1}, {-3, 1}, {-3, 2}, {-2, -1}, {-3, -1}, {-3, -2}});
static vector<vec> D4 = vector<vec>({{0, -1}, {1, -2}, {1, -3}, {2, -3}, {-1, -2}, {-1, -3}, {-2, -3}});

static vec v1(1, -1);
static vec v2(2, 2);

int run_tests(vec &line, vector<vec> &A, vector<vec> &B, bool same_side)
{
    int error = 0;

    for(vec &p1: A)
        for(vec &p2: B)
            if(sameSide(line, p1, p2) != same_side)
            {
                cout << "error: vectors should " << (same_side ? "" : "not ") << "be on the same side: " << p1 << " ; " << p2 << endl;
                error++;
            }
    
    return error;
}

int main()
{
    cout << endl << "TEST D1 AND D2 OVER V1" << endl;

    int errors = run_tests(v1, D1, D2, true);

    size_t test_size = D1.size() * D2.size();

    cout << "passing: " << (test_size - errors) << " / " << test_size << endl;



    cout << endl << "TEST D1 AND D3 OVER V1" << endl;

    errors = run_tests(v1, D1, D3, false);

    test_size = D1.size() * D3.size();

    cout << "passing: " << (test_size - errors) << " / " << test_size << endl;



    cout << endl << "TEST D1 AND D3 OVER V2" << endl;

    errors = run_tests(v2, D1, D3, false);

    test_size = D1.size() * D3.size();

    cout << "passing: " << (test_size - errors) << " / " << test_size << endl;


    cout << endl << "TEST D1 AND D4 OVER V2" << endl;

    errors = run_tests(v2, D1, D4, true);

    test_size = D1.size() * D4.size();

    cout << "passing: " << (test_size - errors) << " / " << test_size << endl;
}
