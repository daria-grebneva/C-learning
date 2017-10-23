#include "stdafx.h"

#include "Game.h"
#include "sheet.h"
#include "Utils.h"
#include <iostream>
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
		CheckEvents();
		Update();
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

void CGame::Update()
{
	m_hero.Update(sf::Vector2f(m_mousePosition));
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

//bool CGame::PositionRight(const CEnemy & enemy, const CAgar & player, const int radius) 
//{
//	if ((enemy.GetPosition().x - player.GetPosition().x) <= radius && (enemy.GetPosition().x + player.GetRadius() / 2 - player.GetPosition.x) > 0)
//	{
//		return true;
//	}
//	return false;
//}

//bool CGame::PositionLeft(const CEnemy & enemy, const CAgar & player, const int radius)
//{
//	if ((player.GetPosition().x - enemy.GetPosition().x) <= radius && (player.GetPosition().x + player.GetRadius() / 2 - enemy.GetPosition().x) > 0)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool CGame::PositionUp(const CEnemy & enemy, const CAgar & player, const int radius) 
//{
//	if ((player.GetPosition().y - enemy.GetPosition().y) < radius && (player.GetPosition().y + enemy.GetRadius() / 2 - enemy.GetPosition().y) > 0)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool CGame::PositionDown(const CEnemy & enemy, const CAgar & player, const int radius) 
//{
//	if ((enemy.GetPosition().y - player.GetPosition().y) < radius && (enemy.GetPosition().y + player.GetRadius() / 2 - player.GetPosition().y) > 0)
//	{
//		return true;
//	}
//	return false;
//}