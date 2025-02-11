
#pragma once

#include "../test.hpp"

#include <string>

struct build_input
{
    int value;
};

struct build_output
{
    std::string s;

    inline std::string to_string()
    {
        return s;
    }

    inline bool compare(const build_output &o)
    {
        return s == o.s;
    }
};

void test_build();
