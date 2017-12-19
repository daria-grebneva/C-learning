#include "stdafx.h"

#include "RatingTable.h"

namespace
{

static const auto COLOR_CLIENT = sf::Color({ 159, 255, 34 });

static const auto COLOR_ENEMY = sf::Color({ 199, 159, 40 });

}

RatingTable::RatingTable(sf::RenderWindow & window, CAssets & assets)
	:m_assets(assets)
	,m_window(window)

{
	m_background.setSize(TABLE_SIZE);
	m_background.setFillColor(sf::Color({ 37, 66, 144, 30 }));
}

sf::Vector2f RatingTable::GetPosition() const
{
	return m_background.getPosition();
}

void RatingTable::Draw(sf::RenderWindow & window) const
{
	window.draw(m_background);
}

void RatingTable::SetPosition(const sf::Vector2f & center)
{
	const int xCoord = WINDOW_SIZE.x / 2 - m_background.getSize().x;
	const int yCoord = - (WINDOW_SIZE.y / 2);
	m_background.setPosition(center + sf::Vector2f(xCoord, yCoord));
}
