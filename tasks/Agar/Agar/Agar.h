#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update(const sf::Vector2i & pos, float dt);
	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	void SetRadius(float newRadius);

private:
	float m_acceleration = 0.0001f;
	sf::CircleShape m_body;
};
