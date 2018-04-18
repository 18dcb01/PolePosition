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
	sf::RenderWindow window(sf::VideoMode(512, 448), "Pole Position");
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

		//Pre qualifying things

		game.qualify();

		//end screen things

		//reset as needed

		//if qualified, begin things for race

		//pre race things

		//game.race();

		//end screen things

		//make sure score is handled

		window.display();
	}

	return 0;
}