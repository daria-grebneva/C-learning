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
	sf::Vector2f fieldSize(WINDOW_SIZE);
	sf::Vector2f mousePos = GetPosition() - 0.5f * fieldSize + sf::Vector2f(pos);
	sf::Vector2f path = mousePos - GetPosition() - sf::Vector2f(GetRadius(), GetRadius());
	if (hypotf(path.x, path.y) > numeric_limits<float>::epsilon())
	{
		const auto distance = hypotf(path.x, path.y);
		sf::Vector2f direction = path / distance;
		if (distance > 5.f)
		{
			sf::Vector2f agarPosition = GetPosition() + direction * m_acceleration * dt;
			m_body.setPosition(agarPosition);
		}
	}
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
