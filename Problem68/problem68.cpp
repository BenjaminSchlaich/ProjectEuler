
#include <iostream>
#include <list>
#include <set>

#include "../useful.hpp"

using namespace std;

// read the input as concatenated triples
unsigned long readSets(string s);

// checks whether the 10 (9) is inside, if so true.
bool tooLong(const string &s);

int main(int argc, char *argv[])
{
    ///*
    list<string> perms = permutations("0123456789");

    cout << "Computed all permutations." << endl;

    // don't allow the 10 to be inside the ring:
    for(auto it=perms.begin(); it!=perms.end(); it++)
        while(it!=perms.end() && tooLong(*it))
            it = perms.erase(it);

    cout << "Removed all permutations that are too longs." << endl;

    set<unsigned long> solutions;

    for(auto &s: perms)
    {
        unsigned long l = readSets(s);

        if(l != 0 && !solutions.contains(l))
            solutions.insert(l);
    }

    perms.clear();

    cout << "There are " << solutions.size() << " distinct solutions." << endl;

    unsigned long solution = *solutions.rbegin();   // extract the maximum

    cout << solution << endl;

    return 0;
}

bool tooLong(const string &s)
{
    return s.substr(s.length()/2, s.length()/2).contains('9');
}

unsigned long readSets(string s)
{
    if(s.length() < 6 || s.length() % 2 != 0)   // magic ring exists for every k-polygon with k >= 3 and has 2*k nodes
        throw runtime_error("error in readSets(): invalid input string: " + s);

    // find the entry point:
    int min = s.at(0);
    size_t minI = 0;

    size_t k = s.length()/2;

    for(size_t i=1; i<k; i++)
        if(s.at(i) < min)
        {
            min = s.at(i);
            minI = i;
        }
    
    // now read the string, starting from the entry point:
    string ss;

    size_t i = minI;

    int checksum = 0;

    do
    {
        ss += s.at(i);
        ss += s.at(k + i);
        ss += s.at(k + (i + 1) % k);

        if(checksum == 0)
            checksum = s.at(i) + s.at(k+i) + s.at(k + (i + 1) % k);
        else if(checksum != s.at(i) + s.at(k+i) + s.at(k + (i + 1) % k))
            return 0;

        i++;
        i %= k;
    } while(i != minI);

    for(auto it=ss.begin(); it!=ss.end(); it++)
        if(*it == '9')
        {
            *it = '1';
            ss.insert(next(it), '0');
            it++;
        }
        else
            (*it)++;


    return stoul(ss);
}
