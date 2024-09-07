
#include <vector>

using namespace std;

// Farbe, Wert
typedef std::pair<char, char> card;

#define MAX(a, b) (a > b ? a : b)

void sort(vector<card> &cards);

int isStraightFlush(const vector<card> &cards);

int isFourOfAKind(const vector<card> &cards);

int isFullHouse(const vector<card> &cards);

int isFlush(const vector<card> &cards);

int isStraight(const vector<card> &cards);

int isThreeOfAKind(const vector<card> &cards);

int isTwoPairs(const vector<card> &cards);

int isPair(const vector<card> &cards);

int getHighestRank(const vector<card> &cards);

bool p1HasHighCard(vector<card> &p1, vector<card> &p2);

bool p1Higher(vector<card> &p1, vector<card> &p2);
