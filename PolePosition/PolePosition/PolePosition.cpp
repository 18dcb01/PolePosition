// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::RenderWindow *windowPtr = &window;
	Game game(windowPtr);

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
		window.display();
	}

	return 0;
}

