
#include "test_build.hpp"

#include "problem89.hpp"

using namespace std;

static function<build_output(build_input&)> eval = [](build_input &in) {return (build_output) {build_shortest(in.value)};};

/**
 * all of these come from the problem description and the there linked roman number explanation examples.
 */
vector<test_case<build_input, build_output>> basic_build_tests()
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

    vector<test_case<build_input, build_output>> ts;

    for(size_t i=0; i<ins.size(); i++)
        ts.push_back({
            "build number " + to_string(ins[i]),
            {ins[i]},
            eval,
            {outs[i]}
        });

    return ts;
}

void test_build()
{
    auto t = basic_build_tests();
    run_tests(t, "basic number building tests");
}
