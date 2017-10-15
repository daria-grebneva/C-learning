#pragma once

#include "Agar.h"

class CGame
{
public:
	CGame();

	void DoGameLoop();

private:
	void Update();
	void Render();

	void CheckEvents();
	void CheckMouseEvents(const sf::Event & event);
	sf::Vector2f CheckMouseMove(const sf::Event & event/*, bool & isNeedUpdate*/);
	//void CheckKeyReleased(const sf::Event & event, bool & isNeedUpdate);

	//void CheckCylinderEffect();

	sf::RenderWindow m_window;

	CAgar m_hero;
	//bool m_isLeft = false;
	//bool m_isRight = false;
};