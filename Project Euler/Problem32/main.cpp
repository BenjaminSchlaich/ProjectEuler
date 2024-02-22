// Problem32.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

bool removeFirst(char c, string &s)
{
	for(auto it = s.begin(); it != s.end(); it++)
		if(*it == c)
		{
			s.erase(it);
			return true;
		}
	
	return false;
}

bool validCombination(int a, int b, int c)
{
	const string all = "123456789";

	string combi = to_string(a) + to_string(b) + to_string(c);

	for(char c: all)
		if(!removeFirst(c, combi))
			return false;
	
	return combi.length() == 0;
}

bool isPandigital(int n)
{
	for(int i=1; i*i<=n; i++)
	{
		if(n % i == 0 && validCombination(i, n/i, n))
			return true;
	}

	return false;
}

void testValidCombination()
{
	cout << endl << "running testValidCombination()..." << endl;

	int testTrue[][3] = {
		{123, 456, 789},
		{987, 654, 321},
		{1234, 5678, 9},
		{1, 2, 3456789},
		{543, 21, 6789}
	};
	size_t TT = 5;

	int testFalse[][3] = {
		{1, 2, 3},
		{123, 456, 7890},
		{1234, 4567, 89},
		{9876, 543, 2}
	};
	size_t TF = 4;

	int failures = 0;

	for(int t=0; t<TT; t++)
	{
		if(!validCombination(testTrue[t][0], testTrue[t][1], testTrue[t][2]))
		{
			failures++;
			cout << "testValidCombination(): error for case " << t <<": should return true, but returns false." << endl;
		}
	}

	for(int t=0; t<TF; t++)
	{
		if(validCombination(testFalse[t][0], testFalse[t][1], testFalse[t][2]))
		{
			failures++;
			cout << "testValidCombination(): error for case " << t <<": should return false, but returns true." << endl;
		}
	}

	if(failures == 0)
		cout << "passed all " << (TT+TF) << " test cases." << endl;
	else
		cout << "failed " << failures << "/" << (TT+TF) << " test cases." << endl;
}

int main()
{
	// testValidCombination();

	// if the result had more digits, it could not be built, using the remaining ones.
	int upperBound = 98765;

	int sum = 0;

	for(int n=1; n<=upperBound; n++)
		if(isPandigital(n))
			sum += n;
	
	cout << "The sum of all pandigital products is " << sum << "." << endl;

	return 0;
}
