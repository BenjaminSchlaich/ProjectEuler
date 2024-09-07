
#include <vector>

using namespace std;

// Farbe, Wert
typedef std::pair<char, char> card;

#define MAX(a, b) (a > b ? a : b)

void sort(vector<card> &cards);

int straightFlush(const vector<card> &cards);

int fourOfAKind(const vector<card> &cards);

int fullHouse(const vector<card> &cards);

int flush(const vector<card> &cards);

int straight(const vector<card> &cards);

int threeOfAKind(const vector<card> &cards);

int twoPairs(const vector<card> &cards);

int pair(const vector<card> &cards);

int getHighestRank(const vector<card> &cards);

bool p1HasHighCard(vector<card> &p1, vector<card> &p2);

bool p1Higher(vector<card> &p1, vector<card> &p2);
