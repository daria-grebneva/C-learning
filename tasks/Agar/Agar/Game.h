#pragma once

#include "Agar.h"
#include "Enemies.h"
#include "Meal.h"

class CGame
{
public:
	CGame();

	void DoGameLoop();

private:
	void Update(float dt);
	void Render();

	void CheckEvents();
	void CheckMouseEvents(const sf::Event & event);

	bool CheckPositionRight(const CEnemy & enemy, const CAgar & player, const int radius) const;
	bool CheckPositionLeft(const CEnemy & enemy, const CAgar & player, const int radius) const;
	bool CheckPositionUp(const CEnemy & enemy, const CAgar & player, const int radius) const;
	bool CheckPositionDown(const CEnemy & enemy, const CAgar & player, const int radius) const;
	bool CheckRadiusVisibility(const CEnemy & enemy, const CAgar & player, const int radius) const;
	sf::Vector2f FindNearestDotCoordinate(const CEnemy & enemy);
	
	bool CheckCollision(const CEnemy & enemy, const CMeal & meal);
	bool CheckCollision(const CAgar & player, const CMeal & meal);
	bool CheckCollision(const CAgar & player, const CEnemy & enemy);
	bool CheckCollision(const CEnemy & enemy, const CAgar & player);
	bool CheckCollision(const CEnemy & enemyFirst, const CEnemy & enemySecond);

	bool CanEat(const CEnemy & enemy, const CMeal & meal);
	bool CanEat(const CAgar & player, const CMeal & meal);
	bool CanEat(const CAgar & player, const CEnemy & enemy);
	bool CanEat(const CEnemy & enemy, const CAgar & player);
	bool CanEat(const CEnemy & enemySecond, const CEnemy & enemyFirst);

	void ProcessCollisions(CAgar & player);
	void EnemiesMove(const CAgar & player, float dt);

	sf::RenderWindow m_window;
	sf::Vector2i m_mousePosition;
	CAgar m_hero;
	std::array<CEnemy, NUMBER_ENEMIES> m_enemies;
	std::array<CMeal, NUMBER_MEAL> m_meal;
	sf::View m_view;
	sf::Clock m_clock;
};
