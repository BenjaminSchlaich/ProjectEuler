
#include "poker.hpp"

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

#include <fstream>

using namespace std;

struct pair_hash
{
    size_t operator() (const std::pair<char, char>& p) const
    {
        return ((size_t) p.first << 8) | p.second;
    }
};

ostream &operator<<(ostream &os, card c)
{
    string s = "[";

    switch(c.first)
    {
        case 1:
            s += "Kreuz";
            break;
        case 2:
            s += "Pik";
            break;
        case 3:
            s += "Herz";
            break;
        case 4:
            s += "Karo";
            break;
        default:
            s += "error: " + to_string(c.first);
    }

    s += " ";

    if(c.second < 2)
        s += "error: " + to_string(c.second);
    else if(c.second <= 10)
        s += to_string((int) c.second);
    else
    {
        switch(c.second)
        {
            case 11:
                s += "Bube";
                break;
            case 12:
                s += "Dame";
                break;
            case 13:
                s += "König";
                break;
            case 14:
                s += "Ass";
                break;
            default:
                s += "error: "  + to_string(c.second);
        }
    }

    s += "]";

    os << s;

    return os;
}

bool operator==(const card c, const card d)
{
    return (c.first == d.first) && (c.second == d.second);
}

#define MAX(a, b) (a > b ? a : b)

#define CONTAINS(c) & (1 << c)
#define INSERT(c, s) s |= (1 << c);

static const vector<int(*)(const vector<card> &)> order = {
        isPair, isTwoPairs, isThreeOfAKind, isStraight, isFlush, isFullHouse, isFourOfAKind, isStraightFlush
    };

void sort(vector<card> &cards)
{
    function<bool(const card&, const card&)> cmp = [](const card& c1, const card& c2) {
        return c1.second <= c2.second;
    };

    std::sort(cards.begin(), cards.end(), cmp);
}

// expects sorted cards
int isStraightFlush(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).first != cards.at(0).first || cards.at(i).second != cards.at(i-1).second + 1)
            return 0;
    
    return cards.at(4).second;
}

// expects sorted cards
int isFourOfAKind(const vector<card> &cards)
{
    if(cards.at(0).second == cards.at(3).second)
        return cards.at(3).second;
    else if(cards.at(1).second == cards.at(4).second)
        return cards.at(4).second;
    else
        return 0;
}

// expects sorted cards
int isFullHouse(const vector<card> &cards)
{
    bool valid = cards.at(0) == cards.at(1)
                &&  cards.at(3) == cards.at(4)
                && (cards.at(1) == cards.at(2) || cards.at(2) == cards.at(3));
    
    if(!valid)
        return 0;
    else
        return cards.at(4).second;
}

// expects sorted cards
int isFlush(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).first != cards.at(0).first)
            return 0;
    
    return cards.at(4).second;
}

// expects sorted cards
int isStraight(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).second != cards.at(i-1).second + 1)
            return 0;
    
    return cards.at(4).second;
}

int isThreeOfAKind(const vector<card> &cards)
{
    vector<char> m(16, 0);

    for(const card &c: cards)
    {
        m.at(c.second)++;

        if(m.at(c.second) == 3)
            return c.second;
    }
    
    return 0;
}

int isTwoPairs(const vector<card> &cards)
{
    int s1 = 0, s2 = 0;

    for(const card &c: cards)
        if(s1 CONTAINS(c.second))
            INSERT(c.second, s2)
        else
            INSERT(c.second, s1)
    
    int sting = 0b100;  // 1 << 2
    int count = 0;
    int max = 0;

    for(int i=0; i<13; i++)
    {
        if(sting & s1 & s2)
        {
            count++;
            max = MAX(max, i+2);
        }

        sting <<= 1;
    }
    
    if(count >= 2)
        return max;
    else
        return 0;
}

// this method will not find the higher of two pairs, but choose one arbitrarily.
// that should not matter, as two pairs would be worth more anyways, so this shouldn't be called then.
int isPair(const vector<card> &cards)
{
    int s = 0;

    for(auto &c: cards)
        if(s CONTAINS(c.second))
            return c.second;
        else
            INSERT(c.second, s);
    
    return 0;
}

// will return the rank of the highest figure possible with this hand.
// 0 = high card, 1 = pair, 2 = two pairs, ...
int getHighestRank(vector<card> &cards)
{
    int rank = order.size();

    sort(cards);

    for(auto f = order.rbegin(); f != order.rend(); f++)
        if((*f)(cards))
            break;
        else
            rank--;

    return rank;
}

// expects sorted cards
bool p1HasHighCard(vector<card> &p1, vector<card> &p2)
{
    for(int i=4; i>=0; i--)
        if(p1.at(i).second == p2.at(i).second)
            continue;
        else
            return p1.at(i).second > p2.at(i).second;

    return false;
}

// expects two vectors with exactly 5 cards each.
bool p1Higher(vector<card> &p1, vector<card> &p2)
{
    sort(p1);
    sort(p2);

    int r1 = getHighestRank(p1);
    int r2 = getHighestRank(p2);

    if(r1 > r2)
        return true;
    else if(r1 == r2)
    {
        if(r1 > 0)
        {
            int innerHigh1 = order.at(r1-1)(p1);
            int innerHigh2 = order.at(r2-1)(p2);

            if(innerHigh1 > innerHigh2)
                return true;
            else if(innerHigh1 < innerHigh2)
                return false;
        }

        return p1HasHighCard(p1, p2);
    }
    else
        return false;
}

vector<vector<card>> readFile(string filename)
{
    ifstream ifs(filename);

    if(!ifs.good())
    {
        cout << "Could not open file " << filename << endl;
        return vector<vector<card>>();
    }

    vector<vector<card>> vs;

    while(!ifs.eof())
    {
        string line;

        getline(ifs, line);

        for(int i=0; i<2; i++)
        {
            vector<card> v;

            for(int j=0; j<5; j++)
            {
                int base = 15*i + 3*j;
                char value = line.at(base);
                char color = line.at(base + 1);

                switch(value)
                {
                    case 'T': value = 10;
                        break;
                    case 'J': value = 11;
                        break;
                    case 'Q': value = 12;
                        break;
                    case 'K': value = 13;
                        break;
                    case 'A': value = 14;
                        break;
                    default:
                        value -= '0';
                }

                switch(color)
                {
                    case 'C': color = 1;
                        break;
                    case 'S': color = 2;
                        break;
                    case 'H': color = 3;
                        break;
                    case 'D': color = 4;
                }

                v.push_back({color, value});
            }

            vs.push_back(v);
        }
    }

    return vs;
}
