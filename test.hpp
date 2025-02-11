
#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#define PRINT_STARS std::cout << "****************************************************************************************************" << std::endl;
#define PRINT_LINE std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;

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
void run_tests(std::vector<test_case<IN, OUT>> &ts, std::string suit_name)
{
    std::cout << std::endl << std::endl;
    PRINT_STARS PRINT_LINE
    std::cout << "\t Running test suite ### " << suit_name << " ### ..." << std::endl;
    PRINT_LINE

    int success = 0;
    int failure = 0;
    int error = 0;

    for(int t=0; t<ts.size(); t++)
    {
        std::string test_name = ts[t].name == "" ? (suit_name + "[" + std::to_string(t) + "]") : ts[t].name;

        try
        {
            OUT o = ts[t].f(ts[t].in);

            if(o.compare(ts[t].expected))
            {
                success++;

                std::cout << test_name << " passed (" << o.to_string() << ")" << std::endl;
            }
            else
            {
                failure++;

                std::cout    << "failure in test \"" << test_name
                        << "\": expected " << ts[t].expected.to_string()
                        << ", but got " << o.to_string() << std::endl;
            }
        }
        catch(std::exception e)
        {
            error++;

            std::cout << "error in test \"" << test_name << "\": " << e.what() << std::endl;
        }
    }

    PRINT_LINE
    std::cout << "\t Status Report:" <<
    std::endl << " success: " << success << "/" << ts.size() <<
    std::endl << " failure: " << failure << "/" << ts.size() <<
    std::endl << " errors:  " << error << "/" << ts.size() << std::endl;
    PRINT_LINE PRINT_STARS

    std::cout << std::endl;

    return;
}

#endif  // TEST_HPP
