#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned Factorial(unsigned n)
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
	(n >= 0) ? cout << Factorial(n) << endl : cout << "Your input value cannot be less than zero" << endl;
	return 0;
}

