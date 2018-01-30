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
	/*
	//this all needs to go into a vector dummy
	sf::Vector2u windowSize = window->getSize();
	int width = windowSize.x;
	int height = windowSize.y;
	//Draw the grass
	sf::RectangleShape grass(width, height / 2);
	//Set grass position and color
	grass.setPosition(0, 112);
	grass.setFillColor(sf::Color::Green);
	window->draw(grass);
	*/
}


void Game::drawBackground()
{

}
