#include "stdafx.h"
#include <iostream>

//Если использовать тип данных int - можно вводить числа только до 16

using namespace std;

int Factorial(int n) {
	int f = 1;
	for (int i = 1; i <= n; ++i)
	{
		f = f * i;
	}
	return f;
}

int main()
{
	int n;
	cin >> n;
	cout << Factorial(n);
	return 0;
}

