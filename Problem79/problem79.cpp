
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<string> load_attempts()
{
    ifstream ifs("0079_keylog.txt");

    if(!ifs.good())
        throw runtime_error("could not open the file \"0079_keylog.txt\"");
    
    vector<string> v;

    while(!ifs.eof())
    {
        string s;

        getline(ifs, s);

        v.push_back(s);
    }

    return v;
}

bool wouldWork(string pss, string att)
{
    int iAtt = 0;
    int iPss = 0;

    while(iAtt < att.size())
    {
        char c = att.at(iAtt);
        bool works = false;

        while(iPss < pss.size())
        {
            if(pss.at(iPss) == c)
            {
                iAtt++;
                iPss++;
                works = true;
                break;
            }
            else
                iPss++;
        }

        if(!works)
            return false;
    }

    return true;
}

bool worksAll(string pss, vector<string> &v)
{
    for(string att: v)
        if(!wouldWork(pss, att))
            return false;
    
    return true;
}

int solve()
{
    int password = 0;
    auto v = load_attempts();

    // speed this up a little bit by finding a lower bound:
    unordered_set<char> letters;

    for(string &s: v)
        for(char c: s)
            letters.insert(c);
    
    cout << "lower bound on password length: " << letters.size() << endl;

    password = pow(10, letters.size() - 1);

    while(!worksAll(to_string(password), v))
        password++;
    
    cout << "The solution is: " << password << endl;

    return password;
}

/**
 * build:
 * clang++ -std=c++20 -o problem79 -ferror-limit=1 problem79.cpp
 * 
 * run:
 * ./problem79
 */
int main()
{
    solve();

    /*
    auto v = load_attempts();

    string someSol = "";

    for(string &s: v)
        someSol += s;
    
    cout << worksAll(someSol, v) << endl;

    //*/

    return 0;
}
