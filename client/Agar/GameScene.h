#pragma once

#include <json.hpp>
#include "SocketMaster.h"
#include "Assets.h"
#include "Agar.h"
#include "Enemies.h"
#include "Meal.h"
#include "sheet.h"
#include "AudioPlayer.h"
#include "StartScene.h"
#include "RatingTable.h"

class ÑGameScene
{
public:
	ÑGameScene() = delete;
	ÑGameScene(sf::RenderWindow & window, CAssets assets, SocketMaster & socketMaster);
	~ÑGameScene();

	SceneInfo Advance(float dt);

private:
	void CheckKeyboardEvents(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event);
	void Update(float dt);
	void Render();
	void CheckEvents();
	void ProcessUpdateData(const std::string & path);
	const std::string GetId(const std::string & path);
	void CheckMouseEvents(const sf::Event & event);
	void DrawEnemies(std::array<CEnemy, NUMBER_ENEMIES> & enemy, size_t arrSize, const nlohmann::basic_json<> obj);
	void DrawFood(std::array<CMeal, NUMBER_MEAL> & meal, size_t arrSize, const nlohmann::basic_json<> obj);
	void DrawPlayers(std::vector<CAgar> & agarics, CAgar & agar, const nlohmann::basic_json<> obj, std::string & id, CAgar & agarView);
	void InsertDataIntoTable(const nlohmann::basic_json<> obj);
	void DrawDataTable();

	SceneType m_nextSceneType = SceneType::ÑGameScene;
	sf::RenderWindow & m_window;
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
	std::string m_heroNickname;
	CAgar m_agar; 
	sf::Sprite m_background;
	CAudioPlayer m_audioPlayer;
	SocketMaster & m_socketMaster;
	RatingTable m_table;
	typedef std::map<const float, const std::string> tableMap;
	tableMap m_tableMap;
};
