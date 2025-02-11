
#pragma once

#include "../test.hpp"

#include <string>

struct parse_input
{
    std::string s;
};

struct parse_output
{
    int value;

    inline std::string to_string()
    {
        return std::to_string(value);
    }

    inline bool compare(const parse_output &o)
    {
        return value == o.value;
    }
};

void test_parse();
