#pragma once

#include "Agar.h"
#include "Enemies.h"
#include "Meal.h"
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

	bool PositionRight(const CEnemy & enemy, const CAgar & player, const int radius);
	bool PositionLeft(const CEnemy & enemy, const CAgar & player, const int radius);
	bool PositionUp(const CEnemy & enemy, const CAgar & player, const int radius);
	bool PositionDown(const CEnemy & enemy, const CAgar & player, const int radius);

	sf::RenderWindow m_window;
	sf::Vector2i m_mousePosition;
	CAgar m_hero;
	std::array<CEnemy, NUMBER_ENEMIES> m_enemies;
	std::array<CMeal, NUMBER_MEAL> m_meal;
	sf::View m_view;
};
