#include "stdafx.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game():window(sf::VideoMode(1024,896),"Pole Position")
{
	//Probably something else we should be doing here
}


Game::~Game()
{

}


void Game::play()
{
	//qualifying round
	race();
	if (window.isOpen())
	{
		//second race
		for (int i = 0; i < 7; i++)
			r[i] = Racer(i);
		race();
	}
	//Calls race (twice bc two races)
}


void Game::race()
{
	while (window.isOpen())
	{
		//sfml overhead
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//should maybe get more complicated?
		tick();
	}
	//A loop - continually calls tick
}


void Game::tick()
{
	p.tick();
	if (r[0].getPosy() > -1000)
	{
		for (int i = 0; i < 7; i++)
			r[i].tick();
	}
	render();
	//Calls render, updates player and racers
}


void Game::render()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(rand()%256, rand() % 256, rand() % 256));
	window.clear();
	window.draw(shape);
	window.display();
	//First, drawBackground
	//Then, drawMap
	//Then signs, racers, and the player
}


void Game::drawMap()
{

}


void Game::drawBackground()
{

}
