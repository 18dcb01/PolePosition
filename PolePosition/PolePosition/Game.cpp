#include "stdafx.h"
#include "Game.h"


Game::Game()
{

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
			r[i] = Racer(&window);
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
	//First, drawBackground and drawDashboard
	drawBackground();
	p.drawDashboard();
	//Then, drawMap
	drawMap(&window);
	//Then signs, racers, and the player

}


void Game::drawMap(sf::RenderWindow *window)
{
	//this all needs to go into a vector dummy
	sf::Vector2u windowSize = window->getSize();
	int width = windowSize.x;
	int height = windowSize.y;
	//Draw the grass
	sf::RectangleShape grass(sf::Vector2f(width, height / 2));
	//Set grass position and color
	grass.setPosition(0, 112);
	grass.setFillColor(sf::Color::Green);
	window->draw(grass);
}


void Game::drawBackground()
{

}