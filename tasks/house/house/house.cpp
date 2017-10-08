#include "stdafx.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Window Title");

	//background
	sf::RectangleShape shape1;
	shape1.setSize({ 1000, 800 });
	shape1.setRotation(0);
	shape1.setPosition({ 0, 0 });
	shape1.setFillColor(sf::Color::White);

	//ground of the house
	sf::RectangleShape rectangle1;
	rectangle1.setSize({ 500, 400 });
	rectangle1.setRotation(0);
	rectangle1.setPosition({ 250, 250 });
	rectangle1.setFillColor(sf::Color(255, 135, 124));

	//roof
	sf::ConvexShape trapeze;
	trapeze.setFillColor(sf::Color(76, 40, 37));
	trapeze.setPosition(250, 200);
	trapeze.setPointCount(4);
	trapeze.setPoint(0, { 0, 0 });
	trapeze.setPoint(1, { +480, 0 });
	trapeze.setPoint(2, { +560, 170 });
	trapeze.setPoint(3, { -80, 170 });

	//pipe
	sf::RectangleShape rectangle2;
	rectangle2.setSize({ 50, 150 });
	rectangle2.setRotation(0);
	rectangle2.setPosition({ 600, 120 });
	rectangle2.setFillColor(sf::Color(51, 27, 24));

	//pipe
	sf::RectangleShape rectangle3;
	rectangle3.setSize({ 70, 30 });
	rectangle3.setRotation(0);
	rectangle3.setPosition({ 590, 120 });
	rectangle3.setFillColor(sf::Color(51, 27, 24));

	//smoke
	sf::CircleShape circle1;
	circle1.setRadius(40);
	circle1.setFillColor(sf::Color(198, 229, 229));
	circle1.setPosition(590, 30);

	//smoke
	sf::CircleShape circle2;
	circle2.setRadius(40);
	circle2.setFillColor(sf::Color(198, 229, 229));
	circle2.setPosition(640, 25);

	//smoke
	sf::CircleShape circle3;
	circle3.setRadius(35);
	circle3.setFillColor(sf::Color(198, 229, 229));
	circle3.setPosition(690, 25);

	//smoke
	sf::CircleShape circle4;
	circle4.setRadius(35);
	circle4.setFillColor(sf::Color(198, 229, 229));
	circle4.setPosition(735, 25);

	//door
	sf::RectangleShape rectangle4;
	rectangle4.setSize({ 120, 200 });
	rectangle4.setRotation(0);
	rectangle4.setPosition({ 280, 430 });
	rectangle4.setFillColor(sf::Color(51, 27, 24));

	//door handle
	sf::CircleShape circle5;
	circle5.setRadius(7);
	circle5.setFillColor(sf::Color(0, 0, 0));
	circle5.setPosition(370, 520);

	//window
	sf::RectangleShape rectangle5;
	rectangle5.setSize({ 170, 130 });
	rectangle5.setRotation(0);
	rectangle5.setPosition({ 500, 430 });
	rectangle5.setFillColor(sf::Color(255, 200, 124));

	//window frame
	sf::RectangleShape rectangle6;
	rectangle6.setSize({ 5, 130 });
	rectangle6.setRotation(0);
	rectangle6.setPosition({ 500, 430 });
	rectangle6.setFillColor(sf::Color(51, 27, 24));

	//window frame
	sf::RectangleShape rectangle7;
	rectangle7.setSize({ 5, 130 });
	rectangle7.setRotation(0);
	rectangle7.setPosition({ 670, 430 });
	rectangle7.setFillColor(sf::Color(51, 27, 24));

	//window frame
	sf::RectangleShape rectangle8;
	rectangle8.setSize({ 5, 170 });
	rectangle8.setRotation(90);
	rectangle8.setPosition({ 670, 430 });
	rectangle8.setFillColor(sf::Color(51, 27, 24));

	//window frame
	sf::RectangleShape rectangle9;
	rectangle9.setSize({ 5, 170 });
	rectangle9.setRotation(90);
	rectangle9.setPosition({ 670, 555 });
	rectangle9.setFillColor(sf::Color(51, 27, 24));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(shape1);
		window.draw(rectangle1);
		window.draw(trapeze);
		window.draw(rectangle2);
		window.draw(rectangle3);
		window.draw(circle1);
		window.draw(circle2);
		window.draw(circle3);
		window.draw(circle4);
		window.draw(rectangle4);
		window.draw(circle5);
		window.draw(rectangle5);
		window.draw(rectangle6);
		window.draw(rectangle7);
		window.draw(rectangle8);
		window.draw(rectangle9);

		window.display();
	}
}

