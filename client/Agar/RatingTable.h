#pragma once

#include "stdafx.h"

#include "Assets.h"
#include "sheet.h"

class RatingTable
{
public:
	RatingTable() = delete;
	RatingTable(sf::RenderWindow & window, CAssets & assets);
	void SetPosition(const sf::Vector2f & center);
	void Draw(sf::RenderWindow & window);
	sf::Vector2f GetPosition() const;

private:
	CAssets & m_assets;
	
	sf::RectangleShape m_background;
	sf::RenderWindow & m_window;
};
