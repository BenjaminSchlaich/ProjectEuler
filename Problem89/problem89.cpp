
#include "problem89.hpp"
#include "test_parse.hpp"
#include "test_build.hpp"

#include <fstream>

using namespace std;

/**
 * Convert one single roman character digit to an integer.
 */
int translateChar(char c)
{
    switch(c)
    {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:
            throw runtime_error("translateChar(): " + to_string(c) + " is not a valid roman number literal");
    }
}

/**
 * Parse the roman string representation of a number to an integer.
 */
int parse(string &s)
{
    int res;
    int lastCV;

    if(s.length() == 0)
        return 0;
    else if(s.length() == 1)
        return translateChar(s[0]);
    else
    {
        lastCV = translateChar(s[0]);
        res = lastCV;
    }

    for(int i=1; i<s.length(); i++)
    {
        int cv = translateChar(s[i]);

        if(cv > lastCV)
            res += cv - 2*lastCV;
        else
            res += cv;
        
        lastCV = cv;
    }

    return res;
}

/**
 * Build the shortest roman string representation of an integer.
 */
string build_shortest(int i)
{
    string s = "";

    while(i >= 1000)
    {
        s += 'M';
        i -= 1000;
    }

    if(i >= 900)
    {
        s += "CM";
        i -= 900;
    }

    if(i >= 500)
    {
        s += 'D';
        i -= 500;
    }

    if(i >= 400)
    {
        s += "CD";
        i -= 400;
    }

    while(i >= 100)
    {
        s += 'C';
        i -= 100;
    }

    if(i >= 90)
    {
        s += "XC";
        i -= 90;
    }

    if(i >= 50)
    {
        s += 'L';
        i -= 50;
    }

    if(i>= 40)
    {
        s += "XL";
        i -= 40;
    }

    while(i >= 10)
    {
        s += "X";
        i -= 10;
    }

    if(i == 9)
        return s + "IX";

    if(i >= 5)
    {
        s += 'V';
        i -= 5;
    }

    if(i == 4)
        return s + "IV";
    
    while(i >= 1)
    {
        s += 'I';
        i--;
    }

    return s;
}

vector<string> load()
{
    ifstream ifs("0089_roman.txt");

    if(!ifs.good())
        throw runtime_error("load(): could not open file 0089_roman.txt");

    vector<string> v;
    
    while(!ifs.eof())
    {
        string s;

        getline(ifs, s);

        v.push_back(s);
    }

    return v;
}

/**
 * 1. Load the list of numbers
 * 2. Iterate over the numbers and count the length of the original and shortes representation
 * 3. Return the total difference
 */
int solve()
{
    auto v = load();

    int countOriginal = 0;
    int countCompress = 0;

    // count the original number of letters, as well as the reduced number of letters:
    for(string &s: v)
    {
        countOriginal += s.length();

        // general approach to finding the shortest string: parse the number represented, and build the shortest string of that.
        string compressed(build_shortest(parse(s)));

        countCompress += compressed.length();
    }

    // the result is the difference between the total lengths:
    return countOriginal - countCompress;
}

/**
 * build:
 * clang++ -std=c++20 -Wall -Werror -o problem89 -ferror-limit=1 problem89.cpp test_parse.cpp test_build.cpp
 * 
 * run:
 * ./problem89
 */
int main()
{
    test_parse();

    test_build();

    cout << endl << "Solution: " << solve() << endl;
}
