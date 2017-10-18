#pragma once

#include "Agar.h"
#include "Enemies.h"
#include <array>

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
	std::array<CEnemy, NUMBER_ENEMIES> m_enemies;
	sf::View m_view;
};
