#include "stdafx.h"

#include "Enemies.h"

void CEnemy::Draw(sf::RenderWindow & window) const
{
	window.draw(m_body);
}

void CEnemy::SetColor(const sf::Color & color)
{
	m_body.setFillColor(color);
}

void CEnemy::SetPosition(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}

sf::Vector2f CEnemy::GetPosition() const
{
	return m_body.getPosition();
}

float CEnemy::GetRadius() const
{
	return m_body.getRadius();
}

void CEnemy::SetRadius(float newRadius)
{
	m_body.setRadius(newRadius);
}
