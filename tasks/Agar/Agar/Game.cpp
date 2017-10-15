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
	//bool isNeedUpdate = false;

	//if (isNeedUpdate)
	//{
	m_hero.Move(CheckMouseMove(event).x, CheckMouseMove(event).y);
	//}
}

sf::Vector2f CGame::CheckMouseMove(const sf::Event & event/*, bool & isNeedUpdate*/)
{
	if (event.type == sf::Event::MouseMoved)
	{
		float m_x = event.mouseMove.x;
		float m_y = event.mouseMove.y;
	
		return CheckMouseMove(event) = { m_x, m_y };
	}
	return CheckMouseMove(event) = { 0, 0 };
}

void CGame::Update()
{
	m_hero.Update();
	//CheckCylinderEffect();
}

void CGame::Render()
{
	m_window.clear(WHITE);

	m_hero.Draw(m_window);
}

//void CGame::CheckCylinderEffect()
//{
//	auto agarPosition = m_hero.GetPosition();
//	if (agarPosition.x <= -AGAR_SIZE.x)
//	{
//		m_hero.SetPosition({ WINDOW_SIZE.x - AGAR_SIZE.x, agarPosition.y });
//	}
//	if (agarPosition.x >= WINDOW_SIZE.x)
//	{
//		m_hero.SetPosition({ 0, agarPosition.y });
//	}
//}