
#pragma once

#include "../test.cpp"

struct input
{
    unsigned long C, R, K;
};

struct output
{
    unsigned long value;

    inline std::string to_string()
    {
        return std::to_string(value);
    }

    inline bool compare(const output &o)
    {
        return value == o.value;
    }
};

void test_all();
