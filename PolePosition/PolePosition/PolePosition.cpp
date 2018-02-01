// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <time.h>

using namespace std;


int main()
{
	Player p;
	clock_t t;
	t = clock();

	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		//window.display();

		while (t > clock() - 10) {};
		t = clock();
	}
	return 0;
}

