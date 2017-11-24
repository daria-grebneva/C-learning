#pragma once

#include "SocketMaster.h"
#include "Assets.h"
#include "Agar.h"
#include "Enemies.h"
#include "Meal.h"
#include "sheet.h"

class Application
{
public:
	Application();
	~Application() = default;

	void DoGameLoop();

private:
	void Update();
	void Render();
	void CheckEvents();
	void ProcessUpdateData(const std::string & path);

	sf::RenderWindow m_window;
	sf::Vector2i m_mousePosition;
	CAgar m_hero;
	CAssets m_assets;
	std::array<CEnemy, NUMBER_ENEMIES> m_enemies;
	std::array<CMeal, NUMBER_MEAL> m_meal;
	sf::View m_view;
	sf::Clock m_clock;
	std::array<sf::Color, NUMBER_MEAL> m_meal_color;
	sf::Vector2i CheckMouseEvents(const sf::Event & event);

	SocketMaster m_socketMaster;
};
