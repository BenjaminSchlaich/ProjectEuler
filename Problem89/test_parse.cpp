
#include "test_parse.hpp"

#include "problem89.hpp"

#include <cstdlib>

using namespace std;

static function<parse_output(parse_input&)> eval = [](parse_input &in) {return (parse_output) {parse(in.s)};};

/**
 * all of these come from the problem description and the there linked roman number explanation examples.
 */
vector<test_case<parse_input, parse_output>> basic_parse_tests()
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

    vector<test_case<parse_input, parse_output>> ts;

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
    auto t = basic_parse_tests();
    run_tests(t, "basic parsing tests");
}
