#include "stdafx.h"
#include "Utils.h"
#include "sheet.h"

sf::Color GetRandomColor()
{
	const auto R = rand() % 256;
	const auto G = rand() % 256;
	const auto B = rand() % 256;

	return {
		sf::Uint8(R),
		sf::Uint8(G),
		sf::Uint8(B)
	};
}
sf::Vector2f GetRandomCoordinate()
{
	sf::Vector2i randomCoord = {rand() % (WINDOW_FRAME.x), rand() % (WINDOW_FRAME.y) };
	return { sf::Vector2f(randomCoord) };
}
