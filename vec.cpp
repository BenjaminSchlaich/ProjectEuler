
#include "vec.hpp"

vec::vec(double x, double y)
{
    this->x = x;
    this->y = y;
}

double vec::X() const
{
    return x;
}

double vec::Y() const
{
    return y;
}

void vec::operator+=(const vec &v)
{
    x += v.x;
    y += v.y;
}

void vec::operator-=(const vec &v)
{
    x -= v.x;
    y -= v.y;
}

void vec::operator+=(double a)
{
    x += a;
    y += a;
}

void vec::operator-=(double a)
{
    x -= a;
    y -= a;
}

void vec::operator*=(double a)
{
    x *= a;
    y *= a;
}

std::ostream &operator<<(std::ostream &os, vec v)
{
    os << "{" << v.x << ", " << v.y << "}";
    return os;
}

vec operator+(double a, vec v)
{
    v += a;
    return v;
}

vec operator-(double a, vec v)
{
    v -= a;
    return v;
}

vec operator*(double a, vec v)
{
    v *= a;
    return v;
}

vec operator+(const vec &v1, const vec &v2)
{
    vec ret(v1);

    ret += v2;
    
    return ret;
}

vec operator-(const vec &v1, const vec &v2)
{
    vec ret(v1);

    ret -= v2;
    
    return ret;
}

double operator*(const vec &v1, const vec &v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

vec project(const vec &v, const vec &p)
{
    double alpha = (v*p)/(v*v);

    return alpha*v;
}

vec pDiff(const vec &v, const vec &p)
{
    vec pj = project(v, p);

    return p - pj;
}

bool sameSide(const vec &v, const vec &p1, const vec &p2)
{
    vec d1 = pDiff (v, p1);
    vec d2 = pDiff (v, p2);

    return d1.X() * d2.X() >= 0;
}

bool sameSide(const vec &a, const vec &b, vec p1, vec p2)
{
    vec ab = b - a;

    p1 -= a;
    p2 -= a;

    return sameSide(ab, p1, p2);
}

bool liesOnVector(const vec &v, const vec &p, const double epsilon)
{
    double xScale = p.X() / v.X();

    double yScale = p.Y() / v.Y();

    return abs(xScale - yScale) < epsilon;
}

bool liesOnLine(const vec &a, const vec &b, vec p, const double epsilon)
{
    vec ab = b - a;

    vec pp = p - a;

    return liesOnVector(ab, pp, epsilon);
}
