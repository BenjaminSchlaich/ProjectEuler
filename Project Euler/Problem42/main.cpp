
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int maxCached = 0;
static int iMaxCached = 0;
static auto cache = vector<int>();

bool isTriangleNumber(int n)
{
    if(n <= maxCached)
        return binary_search(cache.begin(), cache.end(), n);
    
    while(maxCached < n)
    {
        iMaxCached++;
        maxCached = iMaxCached * (iMaxCached + 1) / 2;
        cache.push_back(maxCached);
    }

    return maxCached == n;
}

bool isTriangleWord(string &s)
{
    int sum = 0;

    for(char c: s)
        sum += c - 'A' + 1;     // add up alphabetical positions
    
    return isTriangleNumber(sum);
}

void smallTest()
{
    cout << endl << "running smallTest()..." << endl;

    string testTrue[] = {"A", "C", "F", "J", "SKY"};
    int trueL = sizeof(testTrue) / sizeof(string);

    string testFalse[] = {"B", "D", "E", "G", "H", "I", "K", "ASKY"};
    int falseL = sizeof(testFalse) / sizeof(string);

    int failures = 0;

    // run the tests in a zipped fashion, to test if cacheing works for both cases.
    for(int i=0; i<max(trueL, falseL); i++)
    {
        if(i < trueL && !isTriangleWord(testTrue[i]))
        {
            failures++;
            cout << "failed " << testTrue[i] << ": expected true, got false." << endl;
        }
        if(i < falseL && isTriangleWord(testFalse[i]))
        {
            failures++;
            cout << "failed " << testFalse[i] << ": expected false, got true." << endl;
        }
    }

    if(failures == 0)
        cout << "passed all " << trueL + falseL << " test cases." << endl;
    else
        cout << "failed " << failures << "/" << testTrue->length() + testFalse->length() << " test cases." << endl;
}

void solve()
{
    cout << endl << "running solve()..." << endl;

    const string filename = "0042_words.txt";
    ifstream ifs(filename);

    if(!ifs.good())
    {
        cout << "error: could not open file " << filename << ". abort." << endl;
        return;
    }

    int wordCount = 0;
    int triangles = 0;
    
    while(ifs.good())
    {
        char quoteAndComma;
        ifs >> quoteAndComma;

        string word;
        getline(ifs, word, '"');

        if(isTriangleWord(word))
            triangles++;

        ifs >> quoteAndComma;

        if(wordCount++ == 0)
            cout << "The first word is " << word << "." << endl;
        if(!ifs.good())
            cout << "The last word is " << word << "." << endl;
    }

    cout << "Out of " << wordCount << " words, " << triangles << " are triangle words." << endl;
    cout << cache.size() << " triangle numbers had to be computed in total." << endl;
}

int main()
{
    smallTest();

    solve();

    return 0;
}
