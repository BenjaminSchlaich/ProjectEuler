// Problem327.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>   // transport() needs this
#include <cmath>	// round()
#include <stdexcept>

using namespace std;

const int cardLimit = 3;	// this many cards may be held at once
const int doors = 8;		// rooms+1
const int reach = ceil((double) cardLimit / 2) - 1;	// we can carry one card this far and go back to where we came from
int load = reach % 2 == 0 ? 2 : 1;					// if reach is a even number, we can carry two cards at once, else one

vector<int> B(doors, 0);	// represents the actual value of cards in the boxes (B for box)
vector<int> N(doors, 0);	// represents the debit value of cards in the boxes (N for neccessary)

// find out how many cards must be at least
void setN();

int main()
{

}
