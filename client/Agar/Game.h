#pragma once

#include "Assets.h"
#include "GameScene.h"
#include "PauseScene.h"

class CGame
{
public:
	CGame();

	void DoGameLoop();

private:
	CAssets m_assets;
	sf::Clock m_clock;
	sf::RenderWindow m_window;

	ÑGameScene m_gameScene;
	CPauseScene m_pauseScene;
}; 
