// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

void render();
//Called by render, draws the track on the ground.
void drawMap();

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

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

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

