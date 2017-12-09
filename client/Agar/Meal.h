#pragma once

#include "sheet.h"

class CMeal
{
public:
	CMeal() = default;

	void Draw(sf::RenderWindow & window) const;
	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	void SetColor(const sf::Color & color);
	void SetRadius(float newRadius);

private:
	sf::CircleShape m_body;
};
