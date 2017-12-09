#include "stdafx.h"

#include "Meal.h"

void CMeal::Draw(sf::RenderWindow & window) const
{
	window.draw(m_body);
}

void CMeal::SetPosition(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}

sf::Vector2f CMeal::GetPosition() const
{
	return m_body.getPosition();
}

float CMeal::GetRadius() const
{
	return m_body.getRadius();
}

void CMeal::SetColor(const sf::Color & color)
{
	m_body.setFillColor(color);
}

void CMeal::SetRadius(float newRadius)
{
	m_body.setRadius(newRadius);
}
