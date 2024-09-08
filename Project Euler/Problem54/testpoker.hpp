
#pragma once

#include <vector>
#include <string>

bool test_sort();

bool test_isStraightFlush();

bool test_isFourOfAKind();

bool test_isFullHouse();

bool test_isFlush();

bool test_isStraight();

bool test_isThreeOfAKind();

bool test_isTwoPairs();

bool test_isPair();

bool test_getHighestRank();

bool test_p1HasHighCard();

bool test_p1Higher();

bool test_readFile();

void runTestSuite(std::vector<bool(*)()> tests, std::string name);
