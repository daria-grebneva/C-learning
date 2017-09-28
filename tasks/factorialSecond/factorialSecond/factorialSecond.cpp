#include "stdafx.h"
#include <iostream>

//Если использовать тип данных int - можно вводить числа только до 16

using namespace std;

int Factorial(int n) {
	if (n == 1) {
		return 1;
	}
	else {	
		return Factorial(n - 1) * (n);
	}
	
}

int main()
{
	int n;
	cin >> n;
	cout << Factorial(n);
	return 0;
}