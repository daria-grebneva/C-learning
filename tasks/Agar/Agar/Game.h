#pragma once

#include "Agar.h"

class CGame
{
public:
	CGame();

	void DoGameLoop();

private:
	void Update(sf::Vector2f pos);
	void Render();

	void CheckEvents();
	void CheckMouseEvents(const sf::Event & event);

	sf::RenderWindow m_window;
	sf::Vector2i m_mousePosition;
	CAgar m_hero;
};