#include "stdafx.h"

#include "Game.h"
#include "sheet.h"


CGame::CGame()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, WINDOW_STYLE)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);

	for (auto & enemy : m_enemies)
	{
		enemy.SetPosition(ENEMY_INITIAL_POSITION);
	}
	m_enemies[0].SetPosition(AGAR_INITIAL_POSITION);
	m_enemies[1].SetPosition(sf::Vector2f(150, 600));
	m_enemies[2].SetPosition(sf::Vector2f(-200, 400));
	m_enemies[3].SetPosition(sf::Vector2f(270, -500));
	m_enemies[4].SetPosition(sf::Vector2f(90, 40));
	m_enemies[5].SetPosition(sf::Vector2f(340, -100));

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
		mousePosition = { event.mouseMove.x, event.mouseMove.y };
	}
}

void CGame::Update()
{
	m_hero.Update(sf::Vector2f(mousePosition));	
	for (auto & enemy : m_enemies)
	{
		enemy.Update();
	}
	m_view.setCenter(m_hero.GetPosition());
}

void CGame::Render()
{
	m_window.clear(WHITE);

	for (const auto & enemy : m_enemies)
	{
		enemy.Draw(m_window);
	}
	m_hero.Draw(m_window);
}
