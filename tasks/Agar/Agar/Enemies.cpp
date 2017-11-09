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

	sf::Vector2f path = enemyPosition - GetPosition() - sf::Vector2f(GetRadius(), GetRadius());
	if (std::hypotf(path.x, path.y) > std::numeric_limits<float>::epsilon())
	{
		const auto distance = std::hypotf(path.x, path.y);
		sf::Vector2f unitVectorDirection = path / distance;
		if (distance > DISTANCE_TO_MOVE)
		{
			enemyPosition = GetPosition() + unitVectorDirection * m_velocity * dt;
			m_body.setPosition(enemyPosition);
		}
	}
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
