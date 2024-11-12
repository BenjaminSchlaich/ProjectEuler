
#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include <functional>

template <typename IN, typename OUT>
struct test_case
{
    std::string name;           // name of this test
    IN in;                      // the input given
    std::function<OUT(IN&)> f;   // the function used to evaluate the input
    OUT expected;               // the expected output
};

/**
 * Run given tests. Print the results to std::out.
 */
template <typename IN, typename OUT>
void run_tests(std::vector<test_case<IN, OUT>> &ts, std::string suit_name = "");

#endif  // TEST_HPP
