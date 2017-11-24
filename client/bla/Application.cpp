#include "stdafx.h"

#include "Application.h"
#include "json.hpp"
#include "sheet.h"
#include "SocketMaster.h"

using json = nlohmann::json;

namespace
{

static const auto PORT = "https://127.0.0.1:5000";

}

sf::Color takeJSONColor(nlohmann::basic_json <> colorObj)
{
	const std::string color = colorObj.dump();
	sf::Color newColorObj = {
		uint8_t(std::stoi(color.substr(2, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(4, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(6, 2), nullptr, 16))
	}; 
	return newColorObj;
}

Application::Application()
	:m_socketMaster(PORT)
{
	m_socketMaster.Emit(KEY_NEW_PLAYER);
	m_socketMaster.SetHandler(KEY_UPDATE_DATA, [&](sio::event & e) {
		ProcessUpdateData(e.get_message()->get_string());
	});
	
	const sf::VideoMode videoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 8;
	m_window.create(videoMode, WINDOW_TITLE, WINDOW_STYLE, contextSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);

	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

void Application::ProcessUpdateData(const std::string & path)
{
	auto data = json::parse(path);
	auto foodStringLength = data[KEY_FOOD].size();
	auto food = data[KEY_FOOD];
	auto enemiesStringLength = data[KEY_ENEMIES].size();
	auto enemies = data[KEY_ENEMIES];
	auto player = data[KEY_PLAYERS];
	auto playerStringLength = data[KEY_PLAYERS].size();

	for (size_t i = 0; i < playerStringLength; ++i)
	{
		const auto playerId = player.begin().key();
		const auto colorPlayer = player[playerId]["color"];
		m_hero.SetColor(takeJSONColor(colorPlayer));
		sf::Vector2f agarPosition = sf::Vector2f((float(player[playerId]["x"]) *  float(FIELD_SIZE.x)), (float(player[playerId]["y"]) *  float(FIELD_SIZE.y)));
		m_hero.SetPosition(agarPosition);
		m_hero.SetRadius(float(player[player.begin().key()]["radius"]) * FIELD_COEF);
	}
	
	for (size_t n = 0; n < foodStringLength; ++n)
	{
		auto colorFood = food[n]["color"];
		m_meal[n].SetColor(takeJSONColor(colorFood));
		m_meal[n].SetPosition(sf::Vector2f(float(food[n]["x"]) * FIELD_SIZE.x, float(food[n]["y"]) * FIELD_SIZE.y));
		m_meal[n].SetRadius(float(food[n]["radius"]) * FIELD_COEF);
	}

	for (size_t j = 0; j < enemiesStringLength; ++j)
	{
		auto colorEnemy = enemies[j]["color"];
		m_enemies[j].SetColor(takeJSONColor(colorEnemy));
		m_enemies[j].SetPosition(sf::Vector2f(float(enemies[j]["x"]) * FIELD_SIZE.x, float(enemies[j]["y"]) * FIELD_SIZE.y));
		m_enemies[j].SetRadius(float(enemies[j]["radius"]) * FIELD_COEF);
	}
}

void Application::DoGameLoop()
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
	}
}

void Application::CheckEvents()
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

sf::Vector2i Application::CheckMouseEvents(const sf::Event & event)
{
	sf::Vector2i mousePosition = { 0,  0 };
	if (event.type == sf::Event::MouseMoved)
	{
		mousePosition = { event.mouseMove.x, event.mouseMove.y };
	}
	else
	{
		mousePosition = sf::Vector2i(m_hero.GetPosition());
	}
	return mousePosition;
}

void Application::Update()
{
	json playerInfo;
	sf::Vector2f fieldSize(WINDOW_SIZE);
	sf::Vector2f mousePos = m_hero.GetPosition() - 0.5f * fieldSize + sf::Vector2f((float(m_mousePosition.x)), (float(m_mousePosition.y)));
	playerInfo["x"] = (mousePos.x / float(FIELD_SIZE.x));
	playerInfo["y"] = (mousePos.y / float(FIELD_SIZE.y));
	m_socketMaster.Emit(KEY_MOVEMENT, playerInfo.dump());
	m_view.setCenter(m_hero.GetPosition() + m_hero.GetRadius() * sf::Vector2f(1, 1));
	m_window.setView(m_view);
}

void Application::Render()
{
	m_window.clear(PURPLE);
	for (const auto & meal : m_meal)
	{
		meal.Draw(m_window);
	}
	for (const auto & enemy : m_enemies)
	{
		enemy.Draw(m_window);
	}
	m_hero.Draw(m_window);
}
