
#include "testpoker.hpp"

#include "poker.hpp"

using namespace std;

void printStars(int count = 120)
{
    for(int i=0; i<count; i++)
        cout << '*';
    
    cout << endl;
}

void printTitle(string s)
{
    printStars();

    string s2 = "* " + s;

    cout << s2;

    for(int i=s2.length() + 2; i<120; i++)
        cout << ' ';

    cout << " *" << endl;

    printStars();
}

ostream &operator<<(ostream &os, vector<card> &v)
{
    os << "{";

    for(int i=0; i<v.size(); i++)
        os << v.at(i) << (i < v.size()-1 ? ", " : "");
    
    os << "}";

    return os;
}

bool test_sort()
{
    cout << "running test_sort()..." << endl;

    int T = 100;
    int N = 5;
    bool success = true;

    for(int t=0; t<T && success; t++)
    {
        vector<card> v;

        for(int n=0; n<N; n++)
        {
            char color = (rand() % 4) + 1;
            char value = (rand() % 13) + 2;

            v.push_back({color, value});
        }

        sort(v);

        for(int n=1; n<N; n++)
            if(v.at(n-1).second > v.at(n).second)
            {
                cout << "test failure: sort() returned " << v << endl;
                success = false;
                break;
            }
    }

    return success;
}

bool test_isStraightFlush()
{
    cout << "running test_isStraightFlush()..." << endl;

    vector<card> straightFlush = {{3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}};

    vector<card> noStraightFlush = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    sort(straightFlush);
    sort(noStraightFlush);

    return isStraightFlush(straightFlush) && !isStraightFlush(noStraightFlush);
}

bool test_isFourOfAKind()
{
    cout << "running test_isFourOfAKind()..." << endl;

    vector<card> is4 = {{3, 2}, {3, 13}, {3, 2}, {3, 2}, {3, 2}};

    vector<card> no4 = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    sort(is4);
    sort(no4);

    return isFourOfAKind(is4) && !isFourOfAKind(no4);
}

bool test_isFullHouse()
{
    cout << "running test_isFullHouse()..." << endl;

    vector<card> fullHouse = {{3, 2}, {3, 13}, {3, 2}, {3, 13}, {3, 2}};

    vector<card> noFullHouse = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    sort(fullHouse);
    sort(noFullHouse);

    return isFullHouse(fullHouse) && !isFullHouse(noFullHouse);
}

bool test_isFlush()
{
    cout << "running test_isFlush()..." << endl;
    
    vector<card> flush = {{3, 2}, {3, 13}, {3, 2}, {3, 3}, {3, 6}};

    vector<card> noFlush = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    sort(flush);
    sort(noFlush);

    return isFlush(flush) && !isFlush(noFlush);
}

bool test_isStraight()
{
    cout << "running test_isStraight()..." << endl;

    vector<card> straight = {{3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}};

    vector<card> noStraight = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    sort(straight);
    sort(noStraight);

    return isStraight(straight) && !isStraight(noStraight);
}

bool test_isThreeOfAKind()
{
    cout << "running test_isThreeOfAKind()..." << endl;

    vector<card> three = {{3, 5}, {3, 6}, {2, 5}, {1, 8}, {4, 5}};

    vector<card> noThree = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 13}};

    return isThreeOfAKind(three) && !isThreeOfAKind(noThree);
}

bool test_isTwoPairs()
{
    cout << "running test_isTwoPairs()..." << endl;

    vector<card> toPairs = {{3, 5}, {3, 6}, {3, 6}, {3, 8}, {3, 5}};

    vector<card> noTwoPairs = {{1, 2}, {1, 13}, {1, 2}, {3, 3}, {1, 6}};

    return isTwoPairs(toPairs) && !isTwoPairs(noTwoPairs);
}

bool test_isPair()
{
    cout << "running test_isPair()..." << endl;

    vector<card> pair = {{3, 5}, {2, 4}, {1, 6}, {3, 8}, {3, 5}};

    vector<card> noPair = {{1, 2}, {1, 13}, {1, 10}, {3, 3}, {1, 6}};

    return isPair(pair) && !isPair(noPair);
}

bool test_getHighestRank()
{
    cout << "running test_getHighestRank()..." << endl;

    vector<vector<card>> hands = {
        {{1, 2}, {2, 3}, {3, 4}, {4, 2}, {1, 5}},   // pair
        {{1, 2}, {2, 3}, {3, 2}, {4, 5}, {1, 3}},   // two pairs
        {{1, 2}, {2, 3}, {3, 2}, {4, 2}, {1, 5}},   // three of a kind
        {{1, 2}, {2, 3}, {1, 4}, {1, 5}, {1, 6}},   // straight
        {{4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 5}},   // flush
        {{1, 2}, {1, 3}, {1, 3}, {1, 2}, {1, 2}},   // full house
        {{1, 4}, {1, 3}, {1, 4}, {1, 4}, {1, 4}},   // four of a kind
        {{1, 6}, {1, 4}, {1, 5}, {1, 2}, {1, 3}},   // straight flush
    };

    int result;

    for(int i=0; i<hands.size(); i++)
        if((result = getHighestRank(hands.at(i))) != i+1)
        {
            cout << "test failure: getHighestRank() returned " << result
            << " for " << hands.at(i) << ", but expected " << (i+1) << endl;
            return false;
        }
    
    return true;
}

bool test_p1HasHighCard()
{
    cout << "running test_p1HasHighCard()..." << endl;

    return true;
}

bool test_p1Higher()
{
    cout << "running test_p1Higher()..." << endl;

    vector<vector<card>> hands = {
        {{3, 5}, {1, 5}, {2, 6}, {2, 7}, {4, 13}},      // 1
        {{1, 2}, {2, 3}, {2, 8}, {4, 8}, {4, 12}},
        {{4, 5}, {1, 8}, {2, 9}, {2, 11}, {1, 14}},     // 2
        {{1, 2}, {1, 5}, {4, 7}, {2, 8}, {3, 12}},
        {{4, 2}, {1, 9}, {2, 14}, {3, 14}, {1, 14}},    // 3
        {{4, 3}, {4, 6}, {4, 7}, {4, 10}, {4, 12}},
        {{4, 4}, {2, 6}, {3, 9}, {3, 12}, {1, 12}},     // 4
        {{4, 3}, {4, 6}, {3, 7}, {4, 12}, {2, 12}},
        {{3, 2}, {4, 2}, {1, 4}, {4, 4}, {2, 4}},       // 5
        {{1, 3}, {4, 3}, {2, 3}, {2, 9}, {4, 9}},
    };

    vector<bool> p1Wins = {false, true, false, true, true};

    for(int i=0; 2*i<hands.size(); i++)
        if(p1Higher(hands.at(2*i), hands.at(2*i+1)) != p1Wins.at(i))
        {
            cout << "test failure: p1Higher expected " << p1Wins.at(i) << " for "
            << hands.at(2*i) << ", " << hands.at(2*i+1) << ", but got " << !p1Wins.at(i) << endl;

            return false;
        }
    
    return true;
}

bool test_readFile()
{
    cout << "running test_readFile()..." << endl;

    auto vs = readFile("Problem54/0054_poker.txt");

    if(vs.size() != 2000)
        return false;
    
    return vs.at(0).at(0) == ((card) {1, 8}) && vs.at(1999).at(4) == ((card) {1, 6});
}

void runTestSuite(vector<bool(*)()> tests, string name)
{
    int s = 0;  // success
    int f = 0;  // failure

    printTitle("running test suite <" + name + "> ...");

    for(auto &t: tests)
        if(t())
            s++;
        else
        {
            f++;

            cout << "test failed." << endl;
        }
    
    cout << endl << "   STATUS REPORT:" << endl;
    cout << "success: " << s << " | failure: " << f << endl << endl;

    printStars();
}
