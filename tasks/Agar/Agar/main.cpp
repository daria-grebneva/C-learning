#include "stdafx.h"

#include "Game.h"

int main()
{
	srand(unsigned(time(nullptr)));
	CGame game;
	game.DoGameLoop();

	return 0;
}
