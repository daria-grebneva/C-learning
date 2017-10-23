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

void CAgar::Update(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}

void CAgar::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

sf::Vector2f CAgar::GetPosition() const
{
	return m_body.getPosition();
}

float CAgar::GetRadius()
{
	return m_body.getRadius();
}
