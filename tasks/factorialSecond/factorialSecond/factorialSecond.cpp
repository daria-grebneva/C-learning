#include "stdafx.h"
#include <iostream>

using namespace std;

int Factorial(int n) {
	if (n == 1) {
		return 1;
	}
	else {	
		return Factorial(n - 1) * n;
	}
	
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