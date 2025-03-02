
#include "triangle.hpp"

bool contains(Triangle &t, int x, int y, bool strict)
{
    vec p = {(double) x, (double) y};

    vec a = {(double) t.ax, (double) t.ay};
    vec b = {(double) t.bx, (double) t.bx};
    vec c = {(double) t.cx, (double) t.cy};
    
    if(strict && 
        (   liesOnLine(a, b, p)
        ||  liesOnLine(b, c, p)
        ||  liesOnLine(c, a, p)))
        return false;

    return sameSide(a, b, c, p)
        && sameSide(b, c, a, p)
        && sameSide(a, c, b, p);
}

// Function to check if a point (x, y) is inside the rectangle
inline bool containsRect(Rect &t, int x, int y)
{
    return t.x <= x && x <= t.x + t.w
        && t.y <= y && y <= t.y + t.h;
}
