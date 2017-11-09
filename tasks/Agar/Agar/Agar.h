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
	void SetPosition(const sf::Vector2f & pos);

private:
	float m_velocity = START_AGAR_VELOCITY;
	sf::CircleShape m_body;
};
