#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned int Factorial(int n)
{
	int result = 1;
	for (int i = 1; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

int main()
{
	unsigned int n;
	cin >> n;
	if (n >= 0)
	{
		cout << Factorial(n) << endl;
	}
	return 0;
}

