#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update(const sf::Vector2f & pos);
	void Draw(sf::RenderWindow & window);
	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;

private:

	sf::CircleShape m_body;
};
