#include "stdafx.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Window Title");

	sf::RectangleShape ground;
	ground.setSize({ 500, 400 });
	ground.setRotation(0);
	ground.setPosition({ 250, 250 });
	ground.setFillColor(sf::Color(255, 135, 124));

	sf::ConvexShape roof;
	roof.setFillColor(sf::Color(76, 40, 37));
	roof.setPosition(250, 200);
	roof.setPointCount(4);
	roof.setPoint(0, { 0, 0 });
	roof.setPoint(1, { +480, 0 });
	roof.setPoint(2, { +560, 170 });
	roof.setPoint(3, { -80, 170 });

	//pipe
	sf::RectangleShape pipeFirstPart;
	pipeFirstPart.setSize({ 50, 150 });
	pipeFirstPart.setRotation(0);
	pipeFirstPart.setPosition({ 600, 120 });
	pipeFirstPart.setFillColor(sf::Color(51, 27, 24));

	sf::RectangleShape pipeSecondPart;
	pipeSecondPart.setSize({ 70, 30 });
	pipeSecondPart.setRotation(0);
	pipeSecondPart.setPosition({ 590, 120 });
	pipeSecondPart.setFillColor(sf::Color(51, 27, 24));

	sf::CircleShape smokeFirstPart;
	smokeFirstPart.setRadius(40);
	smokeFirstPart.setFillColor(sf::Color(198, 229, 229));
	smokeFirstPart.setPosition(590, 30);

	sf::CircleShape smokeSecondPart;
	smokeSecondPart.setRadius(40);
	smokeSecondPart.setFillColor(sf::Color(198, 229, 229));
	smokeSecondPart.setPosition(640, 25);

	sf::CircleShape smokeThirdPart;
	smokeThirdPart.setRadius(35);
	smokeThirdPart.setFillColor(sf::Color(198, 229, 229));
	smokeThirdPart.setPosition(690, 25);

	sf::CircleShape smokeFourthPart;
	smokeFourthPart.setRadius(35);
	smokeFourthPart.setFillColor(sf::Color(198, 229, 229));
	smokeFourthPart.setPosition(735, 25);

	sf::RectangleShape door;
	door.setSize({ 120, 200 });
	door.setRotation(0);
	door.setPosition({ 280, 430 });
	door.setFillColor(sf::Color(51, 27, 24));

	sf::CircleShape doorHandle;
	doorHandle.setRadius(7);
	doorHandle.setFillColor(sf::Color(0, 0, 0));
	doorHandle.setPosition(370, 520);

	sf::RectangleShape windowGlass;
	windowGlass.setSize({ 170, 130 });
	windowGlass.setRotation(0);
	windowGlass.setPosition({ 500, 430 });
	windowGlass.setFillColor(sf::Color(255, 200, 124));

	sf::RectangleShape firstWindowFrame;
	firstWindowFrame.setSize({ 5, 130 });
	firstWindowFrame.setRotation(0);
	firstWindowFrame.setPosition({ 500, 430 });
	firstWindowFrame.setFillColor(sf::Color(51, 27, 24));

	sf::RectangleShape secondWindowFrame;
	secondWindowFrame.setSize({ 5, 130 });
	secondWindowFrame.setRotation(0);
	secondWindowFrame.setPosition({ 670, 430 });
	secondWindowFrame.setFillColor(sf::Color(51, 27, 24));

	sf::RectangleShape thirdWindowFrame;
	thirdWindowFrame.setSize({ 5, 170 });
	thirdWindowFrame.setRotation(90);
	thirdWindowFrame.setPosition({ 670, 430 });
	thirdWindowFrame.setFillColor(sf::Color(51, 27, 24));

	sf::RectangleShape fourthWindowFrame;
	fourthWindowFrame.setSize({ 5, 170 });
	fourthWindowFrame.setRotation(90);
	fourthWindowFrame.setPosition({ 670, 555 });
	fourthWindowFrame.setFillColor(sf::Color(51, 27, 24));


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
		window.clear(sf::Color::White);
		window.draw(ground);
		window.draw(roof);
		window.draw(pipeFirstPart);
		window.draw(pipeSecondPart);
		window.draw(smokeFirstPart);
		window.draw(smokeSecondPart);
		window.draw(smokeThirdPart);
		window.draw(smokeFourthPart);
		window.draw(door);
		window.draw(doorHandle);
		window.draw(windowGlass);
		window.draw(firstWindowFrame);
		window.draw(secondWindowFrame);
		window.draw(thirdWindowFrame);
		window.draw(fourthWindowFrame);

		window.display();
	}
}

