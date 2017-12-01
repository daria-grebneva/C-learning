#include "stdafx.h"

#include "GameScene.h"
#include "json.hpp"
#include "sheet.h"
#include "SocketMaster.h"

using json = nlohmann::json;

namespace
{

static const auto PORT = "https://127.0.0.1:5000";

}

sf::Color takeJsonColor(nlohmann::basic_json <> colorObj)
{
	const std::string color = colorObj.dump();
	return {
		uint8_t(std::stoi(color.substr(2, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(4, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(6, 2), nullptr, 16))
	}; 
}

GameScene::GameScene()
	:m_socketMaster(PORT)
	,m_audioPlayer("res/sounds/")
{
	m_socketMaster.Emit(KEY_NEW_PLAYER);
	m_socketMaster.SetHandler("player_created", [&](sio::event & m)
	{
		m_heroId = GetId(m.get_message()->get_string());
		m_socketMaster.SetHandler(KEY_UPDATE_DATA, [&](sio::event & e) {
			ProcessUpdateData(e.get_message()->get_string());
		});
	});
	m_audioPlayer.SetVolume(100);
	const sf::VideoMode videoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = ANTIALIASING_LEVEL;
	m_window.create(videoMode, WINDOW_TITLE, WINDOW_STYLE, contextSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);

	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

std::string GameScene::GetId(const std::string & path)
{
	return json::parse(path)["id_player"];
}

void GameScene::ProcessUpdateData(const std::string & path)
{
	const auto data = json::parse(path);
	const auto foodStringLength = data[KEY_FOOD].size();
	const auto food = data[KEY_FOOD];
	const auto enemiesStringLength = data[KEY_ENEMIES].size();
	const auto enemies = data[KEY_ENEMIES];
	const auto player = data[KEY_PLAYERS];
	const auto playerStringLength = data[KEY_PLAYERS].size();
	unsigned index = 0;

	for (auto & player: data[KEY_PLAYERS])
	{
		if (data[KEY_PLAYERS].size() > m_agarics.size())
		{
			m_agar.SetColor(takeJsonColor(player["color"]));
			m_agar.SetPosition(sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y))));
			m_agar.SetRadius(float(player["radius"]) * FIELD_COEF);
			m_agarics.push_back(m_agar);
			if (player["id_player"] == m_heroId)
			{
				m_agarView = m_agar;
			}
		}
		else
		{
			m_agarics[index].SetColor(takeJsonColor(player["color"]));
			m_agarics[index].SetPosition(sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y))));
			m_agarics[index].SetRadius(float(player["radius"]) * FIELD_COEF);
			if (player["id_player"] == m_heroId)
			{
				m_agarView = m_agarics[index];
			}
		}
		++index;
	}

	for (size_t n = 0; n < foodStringLength; ++n)
	{
		auto colorFood = food[n]["color"];
		m_meal[n].SetColor(takeJsonColor(colorFood));
		m_meal[n].SetPosition(sf::Vector2f(float(food[n]["x"]) * FIELD_SIZE.x, float(food[n]["y"]) * FIELD_SIZE.y));
		m_meal[n].SetRadius(float(food[n]["radius"]) * FIELD_COEF);
	}

	for (size_t j = 0; j < enemiesStringLength; ++j)
	{
		auto colorEnemy = enemies[j]["color"];
		m_enemies[j].SetColor(takeJsonColor(colorEnemy));
		m_enemies[j].SetPosition(sf::Vector2f(float(enemies[j]["x"]) * FIELD_SIZE.x, float(enemies[j]["y"]) * FIELD_SIZE.y));
		m_enemies[j].SetRadius(float(enemies[j]["radius"]) * FIELD_COEF);
	}
}

void GameScene::DoGameLoop()
{
	while (m_window.isOpen())
	{
		if (m_socketMaster.IsConnected())
		{
			CheckEvents();
			Update();
			Render();
			m_window.display();
		}
		else 
		{
			CheckEvents();
			m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
			m_background.setTexture(m_assets.BACKGROUND);
			m_window.draw(m_background);
			m_window.setView(m_view);
			m_window.display();
		}
	}
}

void GameScene::CheckEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_mousePosition = CheckMouseEvents(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

sf::Vector2i GameScene::CheckMouseEvents(const sf::Event & event)
{
	sf::Vector2i mousePosition = { 0,  0 };
	if (event.type == sf::Event::MouseMoved)
	{
		mousePosition = { event.mouseMove.x, event.mouseMove.y };
	}
	else
	{
		mousePosition = sf::Vector2i(m_agarView.GetPosition());
	}
	return mousePosition;
}

void GameScene::Update()
{
	json playerInfo;
	sf::Vector2f fieldSize(WINDOW_SIZE);
	sf::Vector2f mousePos = m_agarView.GetPosition() - 0.5f * fieldSize + sf::Vector2f((float(m_mousePosition.x)), (float(m_mousePosition.y)));
	playerInfo["x"] = mousePos.x / float(FIELD_SIZE.x);
	playerInfo["y"] = mousePos.y / float(FIELD_SIZE.y);
	m_socketMaster.Emit(KEY_MOVEMENT, playerInfo.dump());
	m_view.setCenter(m_agarView.GetPosition() + m_agarView.GetRadius() * sf::Vector2f(1, 1));
	m_window.setView(m_view);
}

void GameScene::Render()
{
	m_window.clear(PURPLE);

	for (auto & agar : m_agarics)
	{
		agar.Draw(m_window);
	}

	for (const auto & meal : m_meal)
	{
		meal.Draw(m_window);
	}

	for (const auto & enemy : m_enemies)
	{
		enemy.Draw(m_window);
	}
	
	m_agarView.Draw(m_window);
}
