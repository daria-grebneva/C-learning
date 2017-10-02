#include "stdafx.h"
#include <iostream>

using namespace std;

unsigned int Factorial(int n) 
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
	unsigned int n;
	cin >> n;
	if (n >= 0)
	{
		cout << Factorial(n) << endl;
	}
	return 0;
}