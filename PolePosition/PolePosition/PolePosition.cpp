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
	FreeConsole();
	sf::RenderWindow window(sf::VideoMode(512, 448), "SFML works!");
	sf::Font aClassic;
	if (!aClassic.loadFromFile("Arcade Classic.ttf"))
	{
		cout << "Didn't work dude" << endl;
	}
	sf::Text text;
	text.setFont(aClassic);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		text.setString("   Top 47700  Time    Lap  0\"47");
		text.setPosition(0, 16);
		window.draw(text);
		text.setString(" Score 40570  Time  Speed 113");
		text.setPosition(0, 48);
		window.draw(text);
		window.display();
	}
	return 0;
}

