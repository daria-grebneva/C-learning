#include "stdafx.h"

#include "Agar.h"
#include "sheet.h"

CAgar::CAgar()
{
	m_body.setFillColor(GREEN);
	m_body.setRadius(AGAR_RADIUS);
	m_body.setPosition(AGAR_INITIAL_POSITION);
}

void CAgar::Update()
{
	int mouseX;
	int mouseY;
	Move(GetOffset(mouseX, mouseY));
}

void CAgar::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}
//
//void CAgar::UpdateDirection(int coordX, int coordY)
//{
//	
//}
//
//void CAgar::SetDirection(const DirectionX & newDirection)
//{
//	m_direction = newDirection;
//}
//
//DirectionX CAgar::GetDirection() const
//{
//	return m_direction;
//}
//
//void CAgar::SetPosition(const sf::Vector2f & pos)
//{
//	m_body.setPosition(pos);
//}
//
//sf::Vector2f CAgar::GetPosition() const
//{
//	return m_body.getPosition();
//}

void CAgar::Move(const sf::Vector2f & deltaPosition)
{
	m_body.move(deltaPosition);
}

sf::Vector2f CAgar::GetOffset(int mouseX, int mouseY) const
{
	return sf::Vector2f(GetHorizontalOffset(mouseX), GetVerticalOffset(mouseY));
}

float CAgar::GetHorizontalOffset(int mouseX) const
{
	float positionX = 0;
	positionX = mouseX;
	return positionX;
}

float CAgar::GetVerticalOffset(int mouseY) const
{
	float positionY = 0;
	positionY = mouseY;
	return positionY;
}