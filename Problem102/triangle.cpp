
#include "triangle.hpp"

bool contains(Triangle &t, int x, int y)
{
    vec p = {(double) x, (double) y};

    vec a = {(double) t.ax, (double) t.ay};
    vec b = {(double) t.bx, (double) t.bx};
    vec c = {(double) t.cx, (double) t.cy};

    return sameSide(a, b, c, p)
        && sameSide(b, c, a, p)
        && sameSide(a, c, b, p);
}
