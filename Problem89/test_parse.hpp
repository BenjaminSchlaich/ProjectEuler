
#pragma once

#include "../test.cpp"

#include <string>

struct input
{
    std::string s;
};

struct output
{
    int value;

    inline std::string to_string()
    {
        return std::to_string(value);
    }

    inline bool compare(const output &o)
    {
        return value == o.value;
    }
};

void test_parse();
