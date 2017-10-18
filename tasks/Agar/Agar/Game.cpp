#include "stdafx.h"

#include "Game.h"
#include "sheet.h"

CGame::CGame()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, WINDOW_STYLE)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);
}

void CGame::DoGameLoop()
{
	while (m_window.isOpen())
	{
		CheckEvents();
		Update();
		Render();
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
}

void CGame::Render()
{
	m_window.clear(WHITE);

	m_hero.Draw(m_window);
}
