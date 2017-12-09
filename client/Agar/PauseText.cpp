#include "stdafx.h"
#include "sheet.h"
#include "PauseText.h"

CPauseText::CPauseText(const std::string & text, const sf::Vector2f & position, CAssets & assets)
	:m_assets(assets)
{
	SetPosition(position);
	SetText(text);
	m_text.setFont(m_assets.ARIAL_FONT);
	m_text.setCharacterSize(50);
	m_text.setStyle(sf::Text::Italic);
	m_text.setFillColor(BLUE);
}

void CPauseText::SetPosition(sf::Vector2f position)
{
	m_body.setPosition(position);
	SetText(m_text.getString());
}

float CPauseText::GetStringLengthPx(const std::string & str) const
{
	sf::Text text;
	text.setFont(m_assets.ARIAL_FONT);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Black);
	text.setString(str);
	return (text.findCharacterPos(str.length()).x - text.findCharacterPos(0).x);
}

void CPauseText::SetText(const std::string & text)
{
	m_text.setString(text);
	const float width = m_body.getPosition().x + (PAUSE_TEXT_SIZE.x - GetStringLengthPx(text)) / 2;
	const float height = m_body.getPosition().y;
	m_text.setPosition(width, height);
}

void CPauseText::Draw(sf::RenderWindow & window) const
{
	window.draw(m_text);
}
