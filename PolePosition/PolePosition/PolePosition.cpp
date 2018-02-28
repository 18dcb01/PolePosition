// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 448), "SFML works!");
	sf::RenderWindow *windowPtr = &window;
<<<<<<< HEAD
	Game game(windowPtr);
=======
	std::vector<double> oi;
	Road road(windowPtr, oi);
>>>>>>> e847691b867b3c739aac16cbbbbad4ec9f0d681a


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

<<<<<<< HEAD
		window.clear();
		game.play();
=======
		
		window.clear();
		road.drawRoad();
>>>>>>> e847691b867b3c739aac16cbbbbad4ec9f0d681a
		window.display();

	}

	return 0;
}

