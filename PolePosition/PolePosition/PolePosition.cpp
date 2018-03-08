// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Road.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	window.setFramerateLimit(60);
	sf::RenderWindow *windowPtr = &window;

	sf::Clock clock;

	Game game(windowPtr);

	std::vector<double> oi;
	oi.push_back(2);
	Road road(windowPtr, oi);



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();
		game.play();
		road.draw(100, 0);
		window.display();

		//track framerate
		std::cout << 1.f / clock.getElapsedTime().asSeconds() << '\n';
		clock.restart();
	}

	return 0;
}

