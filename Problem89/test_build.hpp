
#pragma once

#include "../test.cpp"

#include <string>

struct input
{
    int value;
};

struct output
{
    std::string s;

    inline std::string to_string()
    {
        return s;
    }

    inline bool compare(const output &o)
    {
        return s == o.s;
    }
};

void test_build();
