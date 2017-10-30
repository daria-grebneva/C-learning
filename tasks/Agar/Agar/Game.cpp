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

	//m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

void CGame::DoGameLoop()
{
	while (m_window.isOpen())
	{
		const auto dt = m_clock.restart().asSeconds();
		CheckEvents();
		Update(dt);
		Render();
		//m_window.setView(m_view);
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
	m_hero.Update(m_mousePosition, dt);
	for (auto & meal : m_meal)
	{
		//EnemiesMove(m_hero, meal, dt);
	}
	ProcessCollisions(m_hero);
	
	//m_view.setCenter(m_hero.GetPosition());
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

void CGame::EnemiesMove(const CAgar & player, const CMeal & meal, float dt) 
{
	for (auto & enemy : m_enemies) 
	{
		if (CheckRadiusVisibility(enemy, player, CONVERGENCE_RADIUS))
		{
			enemy.Update(sf::Vector2f(player.GetPosition().x, player.GetPosition().y), dt);
		}
		else 
		{
			for (auto & enemy : m_enemies) 
			{
				enemy.Update(FindNearestDotCoordinate(enemy, meal), dt);
			}
		}
	}
}

void CGame::ProcessCollisions(CAgar & player) 
{
	for (auto & enemy : m_enemies) 
	{
		if (CanEat(enemy, player)) 
		{
			//end of Game
		}
		else if (CanEat(player, enemy))
		{
			float newRadius = player.GetRadius() + sqrt(enemy.GetRadius());
			player.SetRadius(newRadius);
			enemy.SetPosition(GetRandomCoordinate());
		}
		else for (auto & enemy : m_enemies) 
		{
			//change enemy coordinate
		}
	}
	for (auto & meal : m_meal) 
	{
		for (auto & enemy : m_enemies) 
		{
			if (CanEat(player, meal))
			{
				float newRadius = player.GetRadius() + sqrt(meal.GetRadius());
				player.SetRadius(newRadius);
				meal.SetPosition(GetRandomCoordinate());
			}
			else if (CanEat(enemy, meal))
			{
				float newRadius = enemy.GetRadius() + sqrt(meal.GetRadius());
				enemy.SetRadius(newRadius);
				meal.SetPosition(GetRandomCoordinate());
			}
		}
	}
}

bool CGame::CanEat(const CEnemy & enemy, const CMeal & meal) 
{
	return ((enemy.GetRadius() > meal.GetRadius()) && (CheckCollision(enemy, meal)));
}

bool CGame::CanEat(const CAgar & player, const CMeal & meal)
{
	return ((player.GetRadius() > meal.GetRadius()) && (CheckCollision(player, meal)));
}

bool CGame::CanEat(const CAgar & player, const CEnemy & enemy)
{
	return ((player.GetRadius() > enemy.GetRadius()) && (CheckCollision(player, enemy)));
}

bool CGame::CanEat(const CEnemy & enemy, const CAgar & player)
{
	return ((enemy.GetRadius() > player.GetRadius()) && (CheckCollision(enemy, player)));
}

//bool CGame::CanEat(const CEnemy & enemy, const CEnemy & enemy)
//{
//	return ((enemy.GetRadius() > enemy.GetRadius()) && (CheckCollision(enemy, enemy)));
//}

bool CGame::CheckCollision(const CEnemy & enemy, const CAgar & player)
{
	if ((((enemy.GetPosition().x - enemy.GetRadius() / 2 - player.GetRadius() / 2) < player.GetPosition().x)
		&& (player.GetPosition().x < (enemy.GetPosition().x + enemy.GetRadius() / 2 + player.GetRadius() / 2)))
		&& (((enemy.GetPosition().y - enemy.GetRadius() - player.GetRadius()) < player.GetPosition().y)
			&& (player.GetPosition().y < (enemy.GetPosition().y + enemy.GetRadius() + player.GetRadius()))))
	{
		return true;
	}
	else return false;
}

bool CGame::CheckCollision(const CAgar & player, const CEnemy & enemy)
{
	if ((((player.GetPosition().x - player.GetRadius() / 2 - enemy.GetRadius() / 2) < enemy.GetPosition().x)
		&& (enemy.GetPosition().x < (player.GetPosition().x + player.GetRadius() / 2 + enemy.GetRadius() / 2)))
		&& (((player.GetPosition().y - player.GetRadius() - enemy.GetRadius()) < enemy.GetPosition().y)
			&& (enemy.GetPosition().y < (player.GetPosition().y + player.GetRadius() + enemy.GetRadius()))))
	{
		return true;
	}
	else return false;
}

bool CGame::CheckCollision(const CAgar & player, const CMeal & meal)
{
	if ((((player.GetPosition().x - player.GetRadius() / 2 - meal.GetRadius() / 2) < meal.GetPosition().x)
		&& (meal.GetPosition().x < (player.GetPosition().x + player.GetRadius() / 2 + meal.GetRadius() / 2)))
		&& (((player.GetPosition().y - player.GetRadius() - meal.GetRadius()) < meal.GetPosition().y)
			&& (meal.GetPosition().y < (player.GetPosition().y + player.GetRadius() + meal.GetRadius()))))
	{
		return true;
	}
	else return false;
}

bool CGame::CheckCollision(const CEnemy & enemy, const CMeal & meal) 
{
	if ((((enemy.GetPosition().x - enemy.GetRadius() / 2 - meal.GetRadius() / 2) < meal.GetPosition().x)
		&& (meal.GetPosition().x < (enemy.GetPosition().x + enemy.GetRadius() / 2 + meal.GetRadius() / 2)))
		&& (((enemy.GetPosition().y - enemy.GetRadius() - meal.GetRadius()) < meal.GetPosition().y)
			&& (meal.GetPosition().y < (enemy.GetPosition().y + enemy.GetRadius() + meal.GetRadius())))) 
	{
		return true;
	}
	else return false;
}

sf::Vector2f CGame::FindNearestDotCoordinate(const CEnemy & enemy, const CMeal & meal)
{
	float coordinateX = 1;
	float coordinateY = 1;
	float newCoordinateX = 0;
	float newCoordinateY = 0;
	unsigned numberNearestDot = 0;
	sf::Vector2f nearestMeal = { 0, 0 };
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
			nearestMeal = { meal.GetPosition().x, meal.GetPosition().y };
		}
	}
	return nearestMeal;
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
