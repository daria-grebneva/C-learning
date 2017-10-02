#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

struct RootsInfo
{
public:
	float first;
	float second;
	unsigned int numberOfRoots;
};

RootsInfo Solve2(int a, int b, int c)
{	
	RootsInfo root;
	const float D = pow(b, 2)- 4 * a * c;
	if (D > 0)
	{
		root.numberOfRoots = 2;
		root.first = (-b + sqrt(D)) / (2 * a);
		root.second = (-b - sqrt(D)) / (2 * a);
	}
	else if (D == 0)
	{
		root.numberOfRoots = 1;
		root.first = (-b) / (2 * a);
	}
	else
	{
		root.numberOfRoots = 0;
	}
	return root;
}

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	if (a == 0) 
	{
		cout << "The equation is not square";
	} 
	else
	{
		const RootsInfo result = Solve2(a, b, c);
		switch (result.numberOfRoots)
		{
			case 2:
				cout << "First root: " << result.first << ' ' << "Second root: " << result.second << endl;
				break;
			case 1:
				cout << "Root: " << result.first << endl;
				break;
			default:
				cout << "No real roots" << endl;
		}
	}
	return 0;
}


