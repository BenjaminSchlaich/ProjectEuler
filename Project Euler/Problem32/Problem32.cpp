// Problem32.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <stdexcept>

typedef unsigned long long ull;

constexpr ull LOW = 123456789;  // the product c must be: c>=LOW
constexpr ull UPP = 987654321;  // the procuct c must be: c<=UPP 

using namespace std;

bool alphabet[9] = { true,true,true,true,true,true,true,true,true };
list<ull> products = list<ull>();

bool listed(ull n)
{
	for (ull i : products)
		if (i == n)
			return true;

	return false;
}

void tryN(ull a, ull b)
{
	ull c = a * b;
	if (c < LOW || c > UPP || listed(c))
		return;
	else
		products.push_back(c);
}

ull p10(int base)
{
	ull r = 1;
	while(base-- > 0)
		r *= 10;

	return r;
}

void generateA(ull, int);
void generateB(ull a, int da, ull b = 0, int d = 0);

void generateA(ull a=0, int d=0)
{
	if (d < 5)
	{
		for (int i = 1; i < 10; i++)
		{
			if (!alphabet[i - 1])
				continue;

			alphabet[i - 1] = false;
			a += i*p10(d);

			generateA(a, d + 1);
			if(d>3) generateB(a, d+1);

			a -= i * p10(d);
			alphabet[i - 1] = true;
		}
	}
}

void generateB(ull a, int da, ull b, int d)
{
	if (d < 5)
	{
		for (int i = 1; i < 10; i++)
		{
			if (!alphabet[i - 1])
				continue;

			alphabet[i - 1] = false;
			b += i*p10(d);

			generateB(a, da, b, d + 1);

			if(da+d > 4) tryN(a, b);

			b -= i * p10(d);
			alphabet[i - 1] = true;
		}
	}
}

int main()
{
	generateA();
	int i = 0;
	
		for (auto it = products.front(); it != products.back(); it++, i++)
		{
			cout << (it) << endl;
			if (i > 10)
				break;
		}
}
