#include "stdafx.h"
#include "Utils.h"
#include "sheet.h"

sf::Color GetRandomColor()
{
	const auto R = rand() % 256;
	const auto G = rand() % 256;
	const auto B = rand() % 256;

	return
	{
		sf::Uint8(R),
		sf::Uint8(G),
		sf::Uint8(B)
	};
}
sf::Vector2f GetRandomCoordinate()
{
	sf::Vector2u randomCoord = { 1 + rand() % (2 * WINDOW_SIZE.x - 1), 1 + rand() % (2 * WINDOW_SIZE.y - 1) };
	return
	{
		sf::Vector2f(randomCoord)
	};
}
