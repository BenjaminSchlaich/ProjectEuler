
#include "test327.hpp"

#include "solve.hpp"

#include <cstdlib>

using namespace std;

static function<output(input&)> eval = [](input &in) {return (output) {solve(in.C, in.R, in.K)};};

vector<test_case<input, output>> test_C3_R1()
{
    auto v = vector<test_case<input, output>>();

    auto test = [](unsigned long K, unsigned long expected){return (test_case<input, output>) {
        "test for K=" + to_string(K),
        {3, 1, K},
        eval,
        {expected}
    };};

    v.push_back(test(1, 2));
    v.push_back(test(2, 3));
    v.push_back(test(3, 6));
    v.push_back(test(4, 9));
    v.push_back(test(5, 12));
    v.push_back(test(6, 15));
    v.push_back(test(7, 18));
    v.push_back(test(8, 21));
    v.push_back(test(9, 24));
    v.push_back(test(10, 27));

    return v;
}

vector<test_case<input, output>> test_C5_R1()
{
    auto v = vector<test_case<input, output>>();

    auto test = [](unsigned long K, unsigned long expected){return (test_case<input, output>) {
        "test for K=" + to_string(K),
        {5, 1, K},
        eval,
        {expected}
    };};

    v.push_back(test(1, 2));
    v.push_back(test(2, 3));
    v.push_back(test(3, 4));
    v.push_back(test(4, 5));
    v.push_back(test(5, 8));
    v.push_back(test(6, 9));
    v.push_back(test(7, 10));
    v.push_back(test(8, 13));
    v.push_back(test(9, 14));
    v.push_back(test(10, 15));

    return v;
}

vector<test_case<input, output>> test_given()
{
    return {
        {
            "test for C=3, R=6, K=1",
            {3, 6, 1},
            eval,
            {123}
        },
        {
            "test for C=4, R=6, K=1",
            {4, 6, 1},
            eval,
            {23}
        }
    };
}

void test_all()
{
    auto t = test_C3_R1();
    run_tests(t, "Small test with C=3, R=1");

    t = test_C5_R1();
    run_tests(t, "Small test with C=5, R=1");

    t = test_given();
    run_tests(t, "Tests given by the Task");
}
