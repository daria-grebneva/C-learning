#include "stdafx.h"
#include <iostream>

using namespace std;

int Factorial(int n)
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
	int n;
	cin >> n;
	if (n > 0)
	{
		cout << Factorial(n) << endl;
	}
	else
	{
		cout << "Your number must be more than 0" << endl;
	}
	return 0;
}

