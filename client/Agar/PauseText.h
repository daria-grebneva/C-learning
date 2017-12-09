#pragma once

#include "stdafx.h"
#include "sheet.h"
#include "Assets.h"

class CPauseText
{
public:
	CPauseText() = delete;
	CPauseText(const std::string & text, const sf::Vector2f & position, CAssets & assets);
	~CPauseText() = default;

	void SetText(const std::string & text);
	void SetPosition(sf::Vector2f position);
	void Draw(sf::RenderWindow & window) const;

private:
	float GetStringLengthPx(const std::string & str) const;

	CAssets & m_assets;
	sf::Sprite m_body;
	sf::Text m_text;
};
