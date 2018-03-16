// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <iostream>
#include "Player.h"
#include <time.h>
#include "Road.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

using namespace std;


int main()
{
	//FreeConsole();
	//basic game run
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	window.setFramerateLimit(60);

	Game game(&window);

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