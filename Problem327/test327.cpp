
#include "test327.hpp"

#include "solve.hpp"

#include <cstdlib>

using namespace std;

static function<output(input&)> eval = [](input &in) {return (output) {solve(in.C, in.R, in.K)};};

vector<test_case<input, output>> test_carryOne()
{
    auto v = vector<test_case<input, output>>();

    v.push_back((test_case<input, output>){
        "simple test: 1, 1, 1",
        {3, 1, 1},
        eval,
        {2}
    });

    return v;
}

void test_all()
{
    auto carry_one_tests = test_carryOne();
    run_tests(carry_one_tests, "test carryOne");
}
