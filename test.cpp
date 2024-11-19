
#include "/Users/benjaminschlaich/Coding/ProjectEuler/test.hpp"

#include <iostream>

#define PRINT_STARS cout << "****************************************************************************************************" << endl;
#define PRINT_LINE cout << "----------------------------------------------------------------------------------------------------" << endl;

using namespace std;

template <typename IN, typename OUT>
void run_tests(std::vector<test_case<IN, OUT>> &ts, std::string suit_name)
{
    cout << endl << endl;
    PRINT_STARS PRINT_LINE
    cout << "\t Running test suite ### " << suit_name << " ### ..." << endl;
    PRINT_LINE

    int success = 0;
    int failure = 0;
    int error = 0;

    for(int t=0; t<ts.size(); t++)
    {
        string test_name = ts[t].name == "" ? (suit_name + "[" + to_string(t) + "]") : ts[t].name;

        try
        {
            OUT o = ts[t].f(ts[t].in);

            if(o.compare(ts[t].expected))
            {
                success++;

                cout << test_name << " passed (" << o.to_string() << ")" << endl;
            }
            else
            {
                failure++;

                cout    << "failure in test \"" << test_name
                        << "\": expected " << ts[t].expected.to_string()
                        << ", but got " << o.to_string() << endl;
            }
        }
        catch(exception e)
        {
            error++;

            cout << "error in test \"" << test_name << "\": " << e.what() << endl;
        }
    }

    PRINT_LINE
    cout << "\t Status Report:" <<
    endl << " success: " << success << "/" << ts.size() <<
    endl << " failure: " << failure << "/" << ts.size() <<
    endl << " errors:  " << error << "/" << ts.size() << endl;
    PRINT_LINE PRINT_STARS

    cout << endl;

    return;
}
