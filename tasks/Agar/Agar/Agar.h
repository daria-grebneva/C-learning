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
	float m_acceleration = 0.0001;
	sf::CircleShape m_body;
	float m_alpha = 0;
};
