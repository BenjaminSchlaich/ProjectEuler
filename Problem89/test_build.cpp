
#include "test_build.hpp"

#include "problem89.hpp"

using namespace std;

static function<output(input&)> eval = [](input &in) {return (output) {build_shortest(in.value)};};

/**
 * all of these come from the problem description and the there linked roman number explanation examples.
 */
vector<test_case<input, output>> basic_tests()
{
    vector<string> outs = {
        "XVI",
        "XLIX",
        "MDCVI"
    };

    vector<int> ins = {
        16,
        49,
        1606
    };

    vector<test_case<input, output>> ts;

    for(size_t i=0; i<ins.size(); i++)
        ts.push_back({
            "build number " + ins[i],
            {ins[i]},
            eval,
            {outs[i]}
        });

    return ts;
}

void test_build()
{
    auto t = basic_tests();
    run_tests(t, "basic number building tests");
}
