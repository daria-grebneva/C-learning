#include "stdafx.h"

#include "Agar.h"
#include "sheet.h"

CAgar::CAgar()
{
	m_body.setFillColor(GREEN);
	m_body.setRadius(AGAR_RADIUS);
	m_body.setPosition(AGAR_INITIAL_POSITION);
}

void CAgar::Update(const sf::Vector2f & pos)
{
	SetPosition(pos);
}

void CAgar::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void CAgar::SetPosition(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}
