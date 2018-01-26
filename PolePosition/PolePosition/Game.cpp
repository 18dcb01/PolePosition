#include "Game.h"
#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	//Map is initialized to all straight for now.
	for (int i = 0; i < 50; i++)
		map.push_back(forward);
}


Game::~Game()
{

}


void Game::play()
{
	//Calls race (twice bc two races)
}


void Game::race()
{
	//A loop - continually calls tick
}


void Game::tick()
{
	//Calls render, updates player and racers
}


void Game::render(sf::RenderWindow *window)
{
	//First, drawBackground
	drawBackground();
	//Then, drawMap
	drawMap(window);
	//Then signs, racers, and the player

}


void Game::drawMap(sf::RenderWindow *window)
{
	sf::Vector2u windowSize = window->getSize();
	int width = windowSize.x;
	int height = windowSize.y;

	//Draw the grass
	sf::Vector2f pos(width, height / 2);
	sf::RectangleShape grass(pos);

	//Set grass position and color
	grass.setPosition(0, 112);
	grass.setFillColor(sf::Color::Green);
	window->draw(grass);

	//Draw track pieces 5 at a time so user can see ahead.

	//3 possible track pieces.
	sf::ConvexShape straight();
	sf::ConvexShape veerRight();
	sf::ConvexShape veerLeft();
}


void Game::drawBackground()
{

}
