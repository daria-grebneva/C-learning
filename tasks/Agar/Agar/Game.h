#pragma once

#include "Agar.h"

class CGame
{
public:
	CGame();

	void DoGameLoop();

private:
	void Update();
	void Render();

	void CheckEvents();
	void CheckMouseEvents(const sf::Event & event);

	sf::RenderWindow m_window;
	sf::Vector2i mousePosition;
	CAgar m_hero;
};
