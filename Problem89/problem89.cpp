
#include "problem89.hpp"
#include "test_parse.hpp"
#include "test_build.hpp"

using namespace std;

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

int parse(string s)
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

/**
 * build:
 * clang++ -std=c++20 -o problem89 -ferror-limit=1 problem89.cpp test_parse.cpp test_build.cpp
 * 
 * run:
 * ./problem89
 */
int main()
{
    test_parse();

    test_build();
}
