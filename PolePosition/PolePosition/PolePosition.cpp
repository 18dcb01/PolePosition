// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "Road.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::RenderWindow *windowPtr = &window;
	//Game game(windowPtr);
	std::vector<double> oi;
	Road road(windowPtr, oi);

	//Vector of sounds.
	std::vector <sf::Sound> sounds;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		road.drawRoad();
		window.clear();
		//game.play();
		window.display();
	}

	return 0;
}

