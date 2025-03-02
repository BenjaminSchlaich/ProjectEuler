
#pragma once

#include "../vec.hpp"

struct Triangle
{
    int ax, ay, bx, by, cx, cy;
};

bool contains(Triangle &t, int x, int y, bool strict = true);

struct Rect {
    int x, y, w, h;
};

// Function to check if a point (x, y) is inside the rectangle
bool containsRect(Rect &t, int x, int y);