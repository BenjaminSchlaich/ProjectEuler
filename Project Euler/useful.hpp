
#pragma once

#include <fstream>
#include <ranges>

// allows printing of iterable classes as an array.
template <std::ranges::range T>
std::ostream &operator<<(std::ostream &os, T r);

// simple prime check in O(sqrt(n)) complexity.
bool isPrime(int n);
