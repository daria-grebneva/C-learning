#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	if ((1 <= n) && (n <= 100)) {
		if ((n % 3 == 0) && (n % 5 == 0)) {
			cout << "FizzBuzz";
		}
		else if (n % 3 == 0) {
			cout << "Fizz";
		}
		else if (n % 5 == 0) {
			cout << "Buzz";
		}
		else {
			cout << n;
		}
	}
	else {
		cout << "Your number is beyond the allowable values";
	}

	return 0;
}