#include "stdafx.h"

#include "PauseScene.h"

namespace
{

static const auto PAUSE_TEXT = "PRESS SPACE TO BACK";

static const sf::Vector2f PAUSE_TEXT_POSITION((WINDOW_SIZE.x / 2 - PAUSE_TEXT_SIZE.x), (WINDOW_SIZE.y / 2 - PAUSE_TEXT_SIZE.y));

}

CPauseScene::CPauseScene(sf::RenderWindow & window, CAssets & assets)
	:m_window(window)
	,m_assets(assets)
	,m_pauseText(PAUSE_TEXT, PAUSE_TEXT_POSITION, m_assets)
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
	m_background.setTexture(m_assets.BACKGROUND);
}

SceneInfo CPauseScene::Advance(float dt)
{
	m_nextSceneType = SceneType::PauseScene;
	CheckEvents();
	Update(dt);
	m_window.setView(m_view);
	Render();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void CPauseScene::CheckEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		CheckKeyboardEvents(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void CPauseScene::CheckKeyboardEvents(const sf::Event & event)
{
	CheckKeyPressed(event);
}

void CPauseScene::CheckKeyPressed(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			m_nextSceneType = SceneType::ÑGameScene;
		default:
			break;
		}
	}
}

void CPauseScene::Update(float dt)
{
	(void)&dt;
}

void CPauseScene::Render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	m_pauseText.Draw(m_window);
}	
