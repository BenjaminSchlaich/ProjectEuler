
#pragma once

#include <iostream>

class vec
{
    friend double operator*(const vec &v1, const vec &v2);
    friend std::ostream &operator<<(std::ostream &os, vec v);

    private:

    double x, y;

    public:

    vec(double x, double y);

    double X();

    double Y();

    void operator+=(double a);

    void operator-=(double a);

    void operator*=(double a);

    void operator+=(const vec &v);

    void operator-=(const vec &v);
};

std::ostream &operator<<(std::ostream &os, vec v);

/// compute the scalar addition, subtraction, multiplication.
vec operator+(double a, vec v);
vec operator-(double a, vec v);
vec operator*(double a, vec v);

// compute the component-wise addition
vec operator+(const vec &v1, const vec &v2);

// compute the component-wise subtraction
vec operator-(const vec &v1, const vec &v2);

// compute the dot product of two vectors
double operator*(const vec &v1, const vec &v2);

// compute the projection vector of p onto v, where p is the coordinate-vector of a point.
vec project(const vec &v, const vec &p);

// compute the vector from project(v, p) to p
vec pDiff(const vec &v, const vec &p);

// returns whether p1 and p2 are on the same side of vector v
bool sameSide(const vec &v, const vec &p1, const vec &p2);

// returns whether p1 and p2 are on the same side of line ab
bool sameSide(const vec &a, const vec &b, vec p1, vec p2);
