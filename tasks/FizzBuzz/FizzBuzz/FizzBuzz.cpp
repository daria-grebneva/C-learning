#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	for (n = 1; n < 101; ++n) 
	{
		if ((n % 3 == 0) && (n % 5 == 0)) 
		{
			cout << "FizzBuzz" << endl;
		}
		else if (n % 3 == 0) 
		{
			cout << "Fizz" << endl;
		}
		else if (n % 5 == 0) 
		{
			cout << "Buzz" << endl;
		}
		else 
		{
			cout << n << endl;
		}
	}
	return 0;
}