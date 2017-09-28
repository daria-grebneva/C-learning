#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

struct roots {
public:
	float first;
	float second;
	int number;
};

roots Solve_2(int a, int b, int c) {
	float D = b * b - 4 * a * c;
	roots Root;
	if (D > 0) {
		Root.first = (-b + sqrt(D)) / (2 * a);
		Root.second = (-b - sqrt(D)) / (2 * a);
		Root.number = 2;
	}
	else if (D == 0) {
		Root.number = 1;
		Root.first = (-b + sqrt(D)) / (2 * a);
	}
	else {
		Root.number = 0;
	}
	return Root;
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (Solve_2(a, b, c).number == 2) {
		cout << "First root: " << Solve_2(a, b, c).first << ' ' << "Second root: " << Solve_2(a, b, c).second;
	}
	else if (Solve_2(a, b, c).number == 1) {
		cout << "Root: " << Solve_2(a, b, c).first;
	}
	else if (Solve_2(a, b, c).number == 0) {
		cout << "No real roots";
	}
	return 0;
}


