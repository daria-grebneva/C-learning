#pragma once

#include "sheet.h"

class CEnemy
{
public:
	CEnemy() = default;

	void Draw(sf::RenderWindow & window) const;
	void SetColor(const sf::Color & color);
	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	void SetRadius(float newRadius);

private:
	sf::CircleShape m_body;
}; 
