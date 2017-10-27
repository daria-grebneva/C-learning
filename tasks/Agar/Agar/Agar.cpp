#include "stdafx.h"

#include "Agar.h"
#include "sheet.h"
#include "Utils.h"

CAgar::CAgar()
{
	m_body.setFillColor(GetRandomColor());
	m_body.setRadius(AGAR_RADIUS);
	m_body.setPosition(AGAR_INITIAL_POSITION);
}

void CAgar::Update(sf::Vector2i & pos, float dt)
{
	sf::Vector2f direction = sf::Vector2f(pos) - GetPosition();
	float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	if (distance > 0) {
		sf::Vector2f(pos) += direction * m_acceleration * dt;
	}
	m_body.setPosition(sf::Vector2f(pos));
}

void CAgar::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

sf::Vector2f CAgar::GetPosition() const
{
	return m_body.getPosition();
}

float CAgar::GetRadius() const
{
	return m_body.getRadius();
}
