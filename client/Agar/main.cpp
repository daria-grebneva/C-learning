#include "stdafx.h"

#include "Game.h"

int main()
{
	srand(unsigned(time(nullptr)));
	CGame app;
	app.DoGameLoop();
}
