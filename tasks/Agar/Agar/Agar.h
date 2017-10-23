#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update(const sf::Vector2f & pos);
	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;
	float GetRadius();

private:

	sf::CircleShape m_body;
};
