#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update(sf::Vector2i & pos, float dt);
	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;

private:
	float m_acceleration = 20;
	sf::CircleShape m_body;
	float m_alpha = 0;
};
