#include "stdafx.h"

#include "Meal.h"
#include "Utils.h"

CMeal::CMeal()
{
	m_body.setFillColor(GetRandomColor());
	m_body.setRadius(MEAL_RADIUS);
}

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
