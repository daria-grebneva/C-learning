#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

struct RootsInfo
{
public:
	float first;
	float second;
	int numberOfRoots;
};

RootsInfo Solve_2(int a, int b, int c)
{	
	RootsInfo root;
	if (a == 0) 
	{
		root.numberOfRoots = 1;
		root.first = (-b / c);
	}
	else 
	{
		const float D = b * b - 4 * a * c;
		if (D > 0)
		{
			root.numberOfRoots = 2;
			root.first = (-b + sqrt(D)) / (2 * a);
			root.second = (-b - sqrt(D)) / (2 * a);
		}
		else if (D == 0)
		{
			root.numberOfRoots = 1;
			root.first = (-b + sqrt(D)) / (2 * a);
		}
		else
		{
			root.numberOfRoots = 0;
		}
	}
	return root;
}

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	RootsInfo result = Solve_2(a, b, c);
	if (result.numberOfRoots == 2)
	{
		cout << "First root: " << result.first << ' ' << "Second root: " << result.second << endl;
	}
	else if (result.numberOfRoots == 1)
	{
		cout << "Root: " << result.first << endl;
	}
	else if (result.numberOfRoots == 0)
	{
		cout << "No real roots" << endl;
	}
	return 0;
}


