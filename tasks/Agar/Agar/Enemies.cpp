#include "stdafx.h"

#include "Enemies.h"
#include "Utils.h"

CEnemy::CEnemy()
{
	m_body.setFillColor(GetRandomColor());
	m_body.setRadius(ENEMY_RADIUS);
}

void CEnemy::Update(const sf::Vector2f & pos, float dt)
{
	sf::Vector2f enemyPosition(pos);
	sf::Vector2f direction = enemyPosition - GetPosition();

	const auto distance = std::hypotf(direction.x, direction.y);
	if (distance > 0) {
		enemyPosition += direction * m_acceleration * dt;
	}
	SetPosition(enemyPosition);
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

float CEnemy::GetRadius() const
{
	return m_body.getRadius();
}

void CEnemy::SetRadius(float newRadius)
{
	m_body.setRadius(newRadius);
}
