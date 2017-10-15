#pragma once

#include "sheet.h"

class CAgar
{
public:
	CAgar();

	void Update();
	void Draw(sf::RenderWindow & window);

	/*void UpdateDirection(int coordX, int coordY);
	void SetDirection(const DirectionX & newDirection);
	DirectionX GetDirection() const;

	void SetPosition(const sf::Vector2f & pos);
	sf::Vector2f GetPosition() const;*/

	void Move(const sf::Vector2f & deltaPosition);

	sf::Vector2f GetOffset(int mouseX, int mouseY) const;

private:
	float GetVerticalOffset(int mouseX) const;
	float GetHorizontalOffset(int mouseY) const;

	//DirectionX m_direction = DirectionX::None;

	sf::CircleShape m_body;
};
