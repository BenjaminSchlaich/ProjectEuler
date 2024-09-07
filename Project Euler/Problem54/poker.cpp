
#include "poker.hpp"

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

using namespace std;

// Farbe, Wert
typedef std::pair<char, char> card;

struct pair_hash
{
    size_t operator() (const std::pair<char, char>& p) const
    {
        return ((size_t) p.first << 8) | p.second;
    }
};

#define MAX(a, b) (a > b ? a : b)

void sort(vector<card> &cards)
{
    function<bool(const card&, const card&)> cmp = [](const card& c1, const card& c2) {
        return c1.second <= c2.second;
    };

    std::sort(cards.begin(), cards.end(), cmp);
}

int isStraightFlush(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).first != cards.at(0).first || cards.at(i).second != cards.at(i-1).second + 1)
            return 0;
    
    return cards.at(4).second;
}

int isFourOfAKind(const vector<card> &cards)
{
    if(cards.at(0).second == cards.at(3).second)
        return cards.at(3).second;
    else if(cards.at(1).second == cards.at(4).second)
        return cards.at(4).second;
    else
        return 0;
}

int isFullHouse(const vector<card> &cards)
{
    unordered_map<const card, char, pair_hash> m;

    for(const card &c: cards)
        if(m.contains(c))
            m.at(c)++;
        else
            m.insert({c, 1});

    if(m.size() != 2)
        return 0;
    
    int max = 0;
    
    for(auto &p: m)
        if(p.second != 3 && p.second != 2)
            return 0;
        else
            max = MAX(max, p.first.second);
    
    return max;
}

int isFlush(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).first != cards.at(0).first)
            return 0;
    
    return cards.at(4).second;
}

int isStraight(const vector<card> &cards)
{
    for(int i=1; i<5; i++)
        if(cards.at(i).second != cards.at(i-1).second + 1)
            return 0;
    
    return cards.at(4).second;
}

int isThreeOfAKind(const vector<card> &cards)
{
    unordered_map<const card, char, pair_hash> m;

    for(const card &c: cards)
        if(m.contains(c))
            m.at(c)++;
        else
            m.insert({c, 1});

    for(auto &p: m)
        if(p.second == 3)
            return p.first.second;
    
    return 0;
}

int isTwoPairs(const vector<card> &cards)
{
    unordered_map<const card, char, pair_hash> m;

    for(const card &c: cards)
        if(m.contains(c))
            m.at(c)++;
        else
            m.insert({c, 1});
    
    int set = 0;

    for(auto &p: m)
        if(p.second == 2)
        {
            if(set)
                return MAX(set, p.first.second);
            else
                set = p.first.second;
        }
    
    return 0;
}

int isPair(const vector<card> &cards)
{
    unordered_set<card, pair_hash> s;

    for(auto &c: cards)
        if(s.contains(c))
            return c.second;
        else
            s.insert(c);
    
    return 0;
}

int getHighestRank(const vector<card> &cards)
{
    auto fs = {
        &isStraightFlush, &isFourOfAKind, &isFullHouse, &isFlush, &isStraight, &isThreeOfAKind, &isTwoPairs, &isPair
    };

    int rank = fs.size();

    for(auto &f: fs)
        if(f(cards))
            return rank;
        else
            rank--;

    return 0;
}

bool p1HasHighCard(vector<card> &p1, vector<card> &p2)
{
    for(int i=4; i>=0; i--)
        if(p1.at(i).second == p2.at(i).second)
            continue;
        else
            return p1.at(i).second > p2.at(i).second;

    return false;
}

bool p1Higher(vector<card> &p1, vector<card> &p2)
{
    sort(p1);
    sort(p2);

    int r1 = getHighestRank(p1);
    int r2 = getHighestRank(p2);

    if(r1 > r2)
        return true;
    else if(r1 == r2)
        return p1HasHighCard(p1, p2);
    else
        return false;
}
