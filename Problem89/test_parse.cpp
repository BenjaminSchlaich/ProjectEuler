
#include "test_parse.hpp"

#include "problem89.hpp"

#include <cstdlib>

using namespace std;

static function<output(input&)> eval = [](input &in) {return (output) {parse(in.s)};};

/**
 * all of these come from the problem description and the there linked roman number explanation examples.
 */
vector<test_case<input, output>> basic_tests()
{
    vector<string> ins = {
        "IIIIIIIIIIIIIIII",
        "VIIIIIIIIIII",
        "VVIIIIII",
        "XIIIIII",
        "VVVI",
        "XVI",
        "XXXXIIIIIIIII",
        "XXXXVIIII",
        "XXXXIX",
        "XLIIIIIIIII",
        "XLVIIII",
        "XLIX",
        "MCCCCCCVI",
        "MDCVI"
    };

    vector<int> outs = {
        16, 16, 16, 16, 16, 16,
        49, 49, 49, 49, 49, 49,
        1606, 1606
    };

    vector<test_case<input, output>> ts;

    for(size_t i=0; i<ins.size(); i++)
        ts.push_back({
            "parse " + ins[i],
            {ins[i]},
            eval,
            {outs[i]}
        });

    return ts;
}

void test_parse()
{
    auto t = basic_tests();
    run_tests(t, "basic parsing tests");
}
