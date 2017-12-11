#pragma once

#include "stdafx.h"

#include "Assets.h"
#include "sheet.h"
#include "SocketMaster.h"

class CStartScene
{
public:
	CStartScene() = delete;
	CStartScene(sf::RenderWindow & window, CAssets & assets, SocketMaster & socketMaster);
	~CStartScene() = default;

	SceneInfo Advance(float dt, bool isConnected);

private:
	void Update(float dt);
	void Render();
	void CheckEvents(bool isConnected);
	void CheckKeyPressed(const sf::Event & event, bool isConnected);
	void CheckKeyboardEvents(const sf::Event & event, bool isConnected);
	void CheckInputText(const sf::Event & event);
	void DrawConnectedInfo(bool isConnected);
	bool IsNicknameStringEmpty() const;

	CAssets & m_assets;
	sf::RenderWindow & m_window;
	SocketMaster & m_socket;
	sf::View m_view;
	sf::Sprite m_background;
	sf::Text m_text;
	sf::Text m_informationText;
	std::string m_nickname;
	std::string m_user;

	SceneType m_nextSceneType = SceneType::CStartScene;
};
