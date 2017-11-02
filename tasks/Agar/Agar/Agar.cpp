#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Agar.h"
#include "sheet.h"
#include "Utils.h"


CAgar::CAgar()
{
	m_body.setFillColor(GetRandomColor());
	m_body.setRadius(AGAR_RADIUS);
	m_body.setPosition(AGAR_INITIAL_POSITION);
}

void CAgar::Update(const sf::Vector2i & pos, float dt)
{
	sf::Vector2f agarPosition(pos);
	sf::Vector2f vectorDirection = (agarPosition - GetPosition());
	sf::Vector2f unitVectorDirection = vectorDirection / hypotf(vectorDirection.x, vectorDirection.y);
	
	const auto distance = std::hypotf(vectorDirection.x, vectorDirection.y);
	if (distance > 0) 
	{
		agarPosition += unitVectorDirection * m_acceleration * dt;
	}
	m_body.setPosition(agarPosition);
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

void CAgar::SetRadius(float newRadius)
{
	m_body.setRadius(newRadius);
}
