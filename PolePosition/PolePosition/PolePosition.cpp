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
	Player p;
	clock_t time;
	time = clock();

	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Texture t;
	t.loadFromFile("10-dithering-opt.jpg");
	sf::Sprite s;
	s.setTexture(t);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(s);
		window.display();
		window.draw(shape);
		window.display();

		p.tick();

		while (time > clock() - 10) {};
		time = clock();
	}
	//basic game run
	Game game;
	game.play();

	return 0;
}

