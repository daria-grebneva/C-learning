#include "stdafx.h"

#include "Game.h"

int main()
{
	try
	{
		CGame app;
		app.DoGameLoop();
	}
	catch (const std::exception & ex)
	{
		std::cerr << std::endl << std::endl << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << std::endl << std::endl << "fuck" << std::endl;
	}
}
