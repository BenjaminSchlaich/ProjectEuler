#pragma once

/*
	This concept defines legal types for which a range restriction can be specified:
	i.e. only if the type allows comparison to check, whether or not a given variable is within its allowed range
*/
template <typename T>
concept Comparable = requires(T a, T b)
{
	a < b;
	a <= b;
	a == b;
	a >= b;
	a > b;
};