
#pragma once

#include "../vec.hpp"

struct Triangle
{
    int ax, ay, bx, by, cx, cy;
};

bool contains(Triangle &t, int x, int y);
