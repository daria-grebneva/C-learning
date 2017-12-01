#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar() = default;

	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	void SetRadius(float newRadius);
	void SetPosition(const sf::Vector2f & pos);
	void SetColor(const sf::Color & color);

private:
	sf::CircleShape m_body;
};
