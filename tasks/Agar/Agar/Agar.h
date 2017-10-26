#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update(sf::Vector2f & pos, float dt);
	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;

private:

	sf::CircleShape m_body;
	float m_alpha = 0;
};
