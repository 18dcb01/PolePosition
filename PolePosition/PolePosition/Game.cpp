#include "stdafx.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game():window(sf::VideoMode(1024,896),"Pole Position")
{

}


Game::~Game()
{

}


void Game::play()
{
	race();
	//initialize racers
	if (window.isOpen())
	{
		race();
	}
	//Calls race (twice bc two races)
}


void Game::race()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		tick();
	}
	//A loop - continually calls tick
}


void Game::tick()
{
	p.tick();
	if (r[0].getPosy() > -1000)
	{
		for (int i = 0; i < 8; i++)
			r[i].tick();
	}
	render();
}


void Game::render()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(rand()%256, rand() % 256, rand() % 256));
	window.clear();
	window.draw(shape);
	window.display();
	//First, drawBackground
	drawBackground();
	//Then, drawMap
	drawMap();
	//Then signs, racers, and the player
}


void Game::drawMap()
{

}


void Game::drawBackground()
{

}
