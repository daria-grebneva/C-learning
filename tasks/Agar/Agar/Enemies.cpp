#include "stdafx.h"

#include "Enemies.h"

CEnemy::CEnemy()
{
	m_body.setFillColor(VIOLET);
	m_body.setRadius(ENEMY_RADIUS);
}

void CEnemy::Update() const
{

}

void CEnemy::Draw(sf::RenderWindow & window) const
{
	window.draw(m_body);
}

void CEnemy::SetPosition(const sf::Vector2f & pos)
{
	m_body.setPosition(pos);
}

sf::Vector2f CEnemy::GetPosition() const
{
	return m_body.getPosition();
}