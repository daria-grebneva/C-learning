#pragma once

#include "stdafx.h"
#include "sheet.h"
#include "Assets.h"
#include "PauseText.h"

class CPauseScene
{
public:
	CPauseScene() = delete;
	CPauseScene(sf::RenderWindow & window, CAssets & assets);
	~CPauseScene() = default;

	SceneInfo Advance(float dt);

private:
	void Update(float dt);
	void Render();

	void CheckEvents();
	void CheckKeyPressed(const sf::Event & event, bool & isNeedUpdate);
	void CheckKeyboardEvents(const sf::Event & event);

	CAssets & m_assets;
	sf::RenderWindow & m_window;

	CPauseText m_pauseText;

	sf::View m_view;
	sf::Sprite m_background;

	SceneType m_nextSceneType = SceneType::PauseScene;
};
