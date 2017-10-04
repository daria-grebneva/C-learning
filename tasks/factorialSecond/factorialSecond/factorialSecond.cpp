#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned Factorial(unsigned n)
{
	int result = 1;
	if ((n != 1) && (n != 0)) 
	{
		result = Factorial(n - 1) * n;
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