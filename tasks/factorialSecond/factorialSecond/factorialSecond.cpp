#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned Factorial(unsigned n)
{
	unsigned result = 1;
	((n != 1) && (n != 0)) ? result = Factorial(n - 1) * n : 1;
	return result;
}

int main()
{
	int n;
	cin >> n;
	if (n >= 0) 
	{
		cout << Factorial(n) << endl;
	}
	else
	{
		cout << "Your input value cannot be less than zero" << endl;
	}
	return 0;
}