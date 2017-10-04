#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned Factorial(unsigned n)
{
	return (n != 0) ? (Factorial(n - 1) * n) : 1;
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