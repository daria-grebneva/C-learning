#include "stdafx.h"

#include "Agar.h"
#include "sheet.h"

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

void CAgar::SetRadius(float newRadius)
{
	m_body.setRadius(newRadius);
	m_body.setPointCount(static_cast<int>(newRadius * float(2 * M_PI)));
}

void CAgar::SetPosition(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}

void CAgar::SetColor(const sf::Color & color)
{
	m_body.setFillColor(color);
}
