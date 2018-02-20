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

using namespace std;


int main()
{
<<<<<<< HEAD
	//basic game run
	Game game;
	game.play();
=======
	FreeConsole();
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	Player p(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		p.tick();
		window.display();
	}
>>>>>>> origin/Words
	return 0;
}