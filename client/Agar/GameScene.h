#pragma once

#include "SocketMaster.h"
#include "Assets.h"
#include "Agar.h"
#include "Enemies.h"
#include "Meal.h"
#include "sheet.h"
#include "AudioPlayer.h"

class GameScene
{
public:
	GameScene();
	~GameScene()
	{
		m_audioPlayer.Stop(); 
	}

	void DoGameLoop();

private:
	void Update();
	void Render();
	void CheckEvents();
	void ProcessUpdateData(const std::string & path);
	std::string GetId(const std::string & path);
	sf::Vector2i CheckMouseEvents(const sf::Event & event);

	sf::RenderWindow m_window;
	sf::Vector2i m_mousePosition;
	CAgar m_agarView;
	CAssets m_assets;
	std::array<CEnemy, NUMBER_ENEMIES> m_enemies;
	std::array<CMeal, NUMBER_MEAL> m_meal;
	sf::View m_view;
	sf::Clock m_clock;
	std::array<sf::Color, NUMBER_MEAL> m_meal_color;
	std::vector<CAgar> m_agarics;
	std::string m_heroId; 
	CAgar m_agar; 
	sf::Sprite m_background;
	CAudioPlayer m_audioPlayer;

	SocketMaster m_socketMaster;
};
