#pragma once

#include "sheet.h"

class CEnemy
{
public:
	CEnemy();

	void Update(const sf::Vector2f & pos, float dt);
	void Draw(sf::RenderWindow & window) const;

	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;
	float GetRadius() const;
	void SetRadius(float newRadius);

private:
	sf::CircleShape m_body;
	float m_acceleration = 10.f;
}; 
