#include "stdafx.h"

#include "Game.h"
#include "sheet.h"
#include "Utils.h"

using namespace std;

CGame::CGame()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, WINDOW_STYLE)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);

	for (auto & enemy : m_enemies)
	{
		enemy.SetPosition(GetRandomCoordinate());
	}

	for (auto & meal : m_meal)
	{
		meal.SetPosition(GetRandomCoordinate());
	}

	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

void CGame::DoGameLoop()
{
	while (m_window.isOpen())
	{
		const auto dt = m_clock.restart().asSeconds();
		CheckEvents();
		Update(dt);
		Render();
		m_window.setView(m_view);
		m_window.display();
	}
}

void CGame::CheckEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		CheckMouseEvents(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void CGame::CheckMouseEvents(const sf::Event & event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		m_mousePosition = { event.mouseMove.x, event.mouseMove.y };
	}
}

void CGame::Update(float dt)
{
	m_hero.Update(sf::Vector2f(m_mousePosition), dt);
	for (auto & meal : m_meal)
	{
		meal.Update();
	}
	for (auto & enemy : m_enemies)
	{
		enemy.Update();
	}
	m_view.setCenter(m_hero.GetPosition());
}

void CGame::Render()
{
	m_window.clear(WHITE);

	for (const auto & meal : m_meal)
	{
		meal.Draw(m_window);
	}
	for (const auto & enemy : m_enemies)
	{
		enemy.Draw(m_window);
	}
	m_hero.Draw(m_window);
}


//void CGame::EnemiesMove(const CEnemy & enemy, const CAgar & player, const CMeal & meal) 
//{
//	for (auto & enemy : m_enemies) 
//	{
//		if (CheckRadiusVisibility(player, enemy, CONVERGENCE_RADIUS))
//		{
//			enemy.SetPosition(sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
//		}
//		else 
//		{
//			for (auto & enemy : m_enemies) 
//			{
//				enemy.SetPosition(FindNearestDotCoordinate(enemy, meal));
//			}
//		}
//	}
//}
//
//void CGame::ProcessCollisions(const CEnemy & enemy, const CAgar & player, const CMeal & meal) 
//{
//	Съедание врагов и игрока
//	for (auto & enemy : m_enemies) 
//	{
//		if (CanEat(enemy, player) == true) 
//		{
//			this._endGame();
//		}
//		else if (CanEat(player, enemy) == true)
//		{
//			/*this.enemies.splice(j, 1);
//			this.numberEatenEnemies++;
//			this._addEnemy();*/
//		}
//		else for (auto & enemy : m_enemies) 
//		{
//			if (СanEat(enemy, enemy) == true) 
//			{
//				/*this.enemies.splice(j, 1);
//				this._addEnemy();*/
//			}
//		}
//	}
//
//	Съедание точки
//	for (auto & meal : m_meal) 
//	{
//		for (auto & enemy : m_enemies) 
//		{
//			if (СanEat(player, meal) == true || CanEat(enemy, meal) == true) 
//			{
//		/*		this.dots.splice(i, 1);
//				this._addDot();*/
//			}
//		}
//	}
//}

bool CGame::CanEat(const CEnemy & enemy, const CMeal & meal) 
{
	return ((enemy.GetRadius() > meal.GetRadius()) && (CheckCollision(enemy, meal) == true));
}

bool CGame::CheckCollision(const CEnemy & enemy, const CMeal & meal) 
{
	if ((((enemy.GetPosition().x - enemy.GetRadius() / 2 - meal.GetRadius() / 2) < meal.GetPosition().x)
		&& (meal.GetPosition().x < (enemy.GetPosition().x + enemy.GetRadius() / 2 + meal.GetRadius() / 2)))
		&& (((enemy.GetPosition().y - enemy.GetRadius() - meal.GetRadius()) < meal.GetPosition().y)
			&& (meal.GetPosition().y < (enemy.GetPosition().y + enemy.GetRadius() + meal.GetRadius())))) 
	{
		//predator.radius = predator.radius + victim.radius * victim.width;
	/*	if (predator.acceleration < LOW_ACCELERATION) {
			predator.acceleration = predator.acceleration - predator.acceleration * victim.width;
		}*/
		return true;
	}
}

sf::Vector2f CGame::FindNearestDotCoordinate(const CEnemy & enemy, const CMeal & meal)
{
	float coordinateX = 1;
	float coordinateY = 1;
	float newCoordinateX = 0;
	float newCoordinateY = 0;
	unsigned numberNearestDot = 0;
	for (unsigned i = 0; i != NUMBER_MEAL; i++) 
	{
		newCoordinateX = abs(enemy.GetPosition().x- meal.GetPosition().x);
		newCoordinateY = abs(enemy.GetPosition().y - meal.GetPosition().y);
		if ((newCoordinateX < coordinateX) && (newCoordinateY < coordinateY)) 
		{
			coordinateX = newCoordinateX;
			coordinateY = newCoordinateY;
			numberNearestDot = i;
		}
		if (i == NUMBER_MEAL - 1) {
			return { meal.GetPosition().x, meal.GetPosition().y };
		}
	}
}

bool CGame::CheckRadiusVisibility(const CEnemy & enemy, const CAgar & player, const int radius) const
{
	return ((CheckPositionRight(enemy, player, radius) || CheckPositionLeft(enemy, player, radius)) && ((CheckPositionDown(enemy, player, radius) || CheckPositionUp(enemy, player, radius))));
}

bool CGame::CheckPositionRight(const CEnemy & enemy, const CAgar & player, const int radius) const
{
	return (((enemy.GetPosition().x - player.GetPosition().x) <= radius) && ((enemy.GetPosition().x + player.GetRadius() / 2 - player.GetPosition().x) > 0));
};

bool CGame::CheckPositionLeft(const CEnemy & enemy, const CAgar & player, const int radius) const
{
	return (((player.GetPosition().x - enemy.GetPosition().x) <= radius) && ((player.GetPosition().x + player.GetRadius() / 2 - enemy.GetPosition().x) > 0));
}

bool CGame::CheckPositionUp(const CEnemy & enemy, const CAgar & player, const int radius) const
{
	return (((player.GetPosition().y - enemy.GetPosition().y) < radius) && ((player.GetPosition().y + enemy.GetRadius() / 2 - enemy.GetPosition().y) > 0));
}

bool CGame::CheckPositionDown(const CEnemy & enemy, const CAgar & player, const int radius) const
{
	return (((enemy.GetPosition().y - player.GetPosition().y) < radius) && ((enemy.GetPosition().y + player.GetRadius() / 2 - player.GetPosition().y) > 0));
}
