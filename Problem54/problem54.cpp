
#include <iostream>

#include "testpoker.hpp"

#include "poker.hpp"

void test_all()
{
    auto tests = {
        test_sort,
        test_isStraightFlush,
        test_isFourOfAKind,
        test_isFullHouse,
        test_isFlush,
        test_isStraight,
        test_isThreeOfAKind,
        test_isTwoPairs,
        test_isPair,
        test_getHighestRank,
        test_p1HasHighCard,
        test_p1Higher,
        test_readFile
    };

    runTestSuite(tests, "poker tests");
}

int solve()
{
    auto vs = readFile("Problem54/0054_poker.txt");

    int countWins = 0;

    for(int i=0; i<1000; i++)
        if(p1Higher(vs.at(2*i), vs.at(2*i+1)))
            countWins++;
    
    return countWins;
}

/**
 * compile:
 * src="Problem54/problem54.cpp Problem54/testpoker.cpp Problem54/poker.cpp"
 * opt="-std=c++2b -pedantic -Wall -Werror -ferror-limit=1 -o Problem54/problem54 -Wno-c99-extensions"
 * build="clang++ $opt $src"
 * eval $build
 */
int main()
{
    test_all();

    cout << endl << endl << "solving the problem: " << solve() << endl;
}
