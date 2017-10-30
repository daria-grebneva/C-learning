#pragma once

#include "sheet.h"

class CMeal
{
public:
	CMeal();

	void Draw(sf::RenderWindow & window) const;
	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;

private:
	sf::CircleShape m_body;
};
