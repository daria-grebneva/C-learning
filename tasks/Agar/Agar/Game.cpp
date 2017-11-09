#include "stdafx.h"

#include "Game.h"
#include "sheet.h"
#include "Utils.h"

using namespace std;

CGame::CGame()
{
	
	const sf::VideoMode videoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 8;
	m_window.create(videoMode, WINDOW_TITLE, WINDOW_STYLE, contextSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);

	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
	m_hero.Update(m_mousePosition, dt);
	EnemiesMove(m_hero, dt);
	ProcessCollisions(m_hero);
	m_view.setCenter(m_hero.GetPosition() + m_hero.GetRadius() * sf::Vector2f(1, 1));
}

void CGame::Render()
{
	m_window.clear(PURPLE);
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

void CGame::EnemiesMove(const CAgar & player, float dt) 
{
	for (auto & enemyFirst : m_enemies) 
	{
		if (CheckRadiusVisibility(enemyFirst, player, CONVERGENCE_RADIUS))
		{
			enemyFirst.Update(sf::Vector2f(player.GetPosition().x, player.GetPosition().y), dt);
		}
		else 
		{
			enemyFirst.Update(FindNearestDotCoordinate(enemyFirst), dt);
		}
	}
}

void CGame::ProcessCollisions(CAgar & player) 
{
	for (auto & enemyFirst : m_enemies) 
	{
		if (CanEat(enemyFirst, player))
		{
			MessageBoxA(nullptr, std::string("Game over").c_str(), "Game over", MB_OK);
			m_window.close();
		}
		else if (CanEat(player, enemyFirst))
		{
			float oldRadius = player.GetRadius();
			float newRadius = std::hypotf(player.GetRadius(), enemyFirst.GetRadius());
			if (newRadius < LIMIT_RADIUS)
			{
				player.SetPosition(player.GetPosition() + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
				player.SetRadius(newRadius);
			}
			enemyFirst.SetRadius(ENEMY_RADIUS);
			enemyFirst.SetPosition(GetRandomCoordinate());
		}
		else for (auto & enemySecond : m_enemies) 
		{
			if (CanEat(enemyFirst, enemySecond))
			{
				float oldRadius = enemyFirst.GetRadius();
				float newRadius = std::hypotf(enemyFirst.GetRadius(), enemySecond.GetRadius());
				if (newRadius < LIMIT_RADIUS)
				{
					enemyFirst.SetPosition(enemyFirst.GetPosition() + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
					enemyFirst.SetRadius(newRadius);
				}
				enemySecond.SetRadius(ENEMY_RADIUS);
				enemySecond.SetPosition(GetRandomCoordinate());
			}
			else if (CanEat(enemySecond, enemyFirst))
			{
				float oldRadius = enemySecond.GetRadius();
				float newRadius = std::hypotf(enemySecond.GetRadius(), enemyFirst.GetRadius());
				if (newRadius < LIMIT_RADIUS)
				{
					enemySecond.SetPosition(enemySecond.GetPosition() + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
					enemySecond.SetRadius(newRadius);
				}
				enemyFirst.SetRadius(ENEMY_RADIUS);
				enemyFirst.SetPosition(GetRandomCoordinate());
			}
			
		}
	}
	for (auto & meal : m_meal) 
	{
		for (auto & enemy : m_enemies) 
		{
			if (CanEat(player, meal))
			{
				float oldRadius = player.GetRadius();
				float newRadius = std::hypotf(player.GetRadius(), meal.GetRadius());
				if (newRadius < LIMIT_RADIUS)
				{
					player.SetPosition(player.GetPosition() + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
					player.SetRadius(newRadius);
				}
				meal.SetPosition(GetRandomCoordinate());
			}
			else if (CanEat(enemy, meal))
			{
				float oldRadius = enemy.GetRadius();
				float newRadius = std::hypotf(enemy.GetRadius(), meal.GetRadius());
				if (newRadius < LIMIT_RADIUS)
				{
					enemy.SetPosition(enemy.GetPosition() + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
					enemy.SetRadius(newRadius);
				}
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

bool CGame::CanEat(const CEnemy & enemySecond, const CEnemy & enemyFirst)
{
	return ((enemySecond.GetRadius() > enemyFirst.GetRadius()) && (CheckCollision(enemySecond, enemyFirst)));
}

bool CGame::CheckCollision(const CEnemy & enemy, const CAgar & player)
{
	return (((abs(enemy.GetPosition().x + enemy.GetRadius() - player.GetRadius() - player.GetPosition().x)) < player.GetRadius() + enemy.GetRadius())
		&& ((abs(enemy.GetPosition().y + enemy.GetRadius() - player.GetRadius() - player.GetPosition().y)) < player.GetRadius() + enemy.GetRadius()));
}

bool CGame::CheckCollision(const CAgar & player, const CEnemy & enemy)
{
	return (((abs(player.GetPosition().x + player.GetRadius() - enemy.GetRadius() - enemy.GetPosition().x)) < enemy.GetRadius() + player.GetRadius())
		&& ((abs(player.GetPosition().y + player.GetRadius() - enemy.GetRadius() - enemy.GetPosition().y)) < enemy.GetRadius() + player.GetRadius()));
}

bool CGame::CheckCollision(const CAgar & player, const CMeal & meal)
{
	return (((abs(player.GetPosition().x + player.GetRadius() - meal.GetRadius() - meal.GetPosition().x)) < meal.GetRadius() + player.GetRadius())
		&& ((abs(player.GetPosition().y + player.GetRadius() - meal.GetRadius() - meal.GetPosition().y)) < meal.GetRadius() + player.GetRadius()));
}

bool CGame::CheckCollision(const CEnemy & enemy, const CMeal & meal) 
{
	return (((abs(enemy.GetPosition().x + enemy.GetRadius() - meal.GetRadius() - meal.GetPosition().x)) < meal.GetRadius() + enemy.GetRadius())
		&& ((abs(enemy.GetPosition().y + enemy.GetRadius() - meal.GetRadius() - meal.GetPosition().y)) < meal.GetRadius() + enemy.GetRadius()));
}

bool CGame::CheckCollision(const CEnemy & enemyFirst, const CEnemy & enemySecond)
{
	return (((abs(enemyFirst.GetPosition().x + enemyFirst.GetRadius() - enemySecond.GetRadius() - enemySecond.GetPosition().x)) < enemySecond.GetRadius() + enemyFirst.GetRadius())
		&& ((abs(enemyFirst.GetPosition().y + enemyFirst.GetRadius() - enemySecond.GetRadius() - enemySecond.GetPosition().y)) < enemySecond.GetRadius() + enemyFirst.GetRadius()));
}

sf::Vector2f CGame::FindNearestDotCoordinate(const CEnemy & enemy)
{
	sf::Vector2f distanceDot = { 0, 0 };
	sf::Vector2f nearestMeal = sf::Vector2f(FIELD_SIZE);
	for (auto & meal : m_meal)
	{
		distanceDot = (enemy.GetPosition() - meal.GetPosition());
		if (hypotf(distanceDot.x, distanceDot.y) < hypotf(nearestMeal.x, nearestMeal.y))
		{
			nearestMeal = distanceDot;
		}
		nearestMeal = (enemy.GetPosition() - nearestMeal);
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
