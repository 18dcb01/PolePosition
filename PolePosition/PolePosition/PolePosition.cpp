// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <iostream>


int main()
{
	sf::Sound sound;
	sf::SoundBuffer buffer;
	buffer.loadFromFile("CarVroom.wav");
	sound.setBuffer(buffer);
	float soundPitch = 1;
	sound.setLoop(true);
	sound.play();
	while (true)
	{
		if (GetKeyState(38)<-5&&soundPitch<5)
			soundPitch += 0.00005;
		if (GetKeyState(40)<-5&&soundPitch>=0.00005)
			soundPitch -= 0.00005;
		std::cout << soundPitch << std::endl;
		sound.setPitch(soundPitch);
	}
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
	}
	//basic game run
	Game game;
	game.play();

	return 0;
}

