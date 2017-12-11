#include "stdafx.h"

#include "Game.h"
#include "sheet.h"

namespace
{

static const auto PORT = "https://127.0.0.1:5000";

}

CGame::CGame()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, WINDOW_STYLE)
	,m_socketMaster(PORT)
	,m_gameScene(m_window, m_assets, m_socketMaster)
	,m_pauseScene(m_window, m_assets)
	,m_startScene(m_window, m_assets, m_socketMaster)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);
	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void CGame::DoGameLoop()
{
	SceneInfo info = SceneInfo(SceneType::CStartScene);
	while (m_window.isOpen())
	{
		const auto dt = m_clock.restart().asSeconds();

		switch (info.nextSceneType)
		{
		case SceneType::ÑGameScene:
			info = m_gameScene.Advance(dt);
			break;
		case SceneType::CStartScene:
			info = m_startScene.Advance(dt, IsConnected());
			break;
		case SceneType::PauseScene:
			info = m_pauseScene.Advance(dt);
			break;
		}
	}
}

bool CGame::IsConnected() const
{
	return m_socketMaster.IsConnected();
}
