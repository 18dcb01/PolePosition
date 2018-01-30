#include "Game.h"
#include "stdafx.h"
#include "Game.h"

Game::Game(sf::RenderWindow *tempWindow)
{
	window = tempWindow;

	//creating background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")
	{

	}
	background.setTexture(backgroundTexture);
}


Game::~Game()
{

}


void Game::play()
{
	//Calls race (twice bc two races)
	tick();
}


void Game::race()
{
	//A loop - continually calls tick
}


void Game::tick()
{
	//Calls render, updates player and racers
	render();
}


void Game::render()
{
	//First, drawBackground
	drawBackground();
	//Then, drawMap
	drawMap();
	//Then signs, racers, and the player

}


//Draw road and grass
void Game::drawMap()
{
	//Draw road
}


void Game::drawBackground()
{
	//Grabbing window size and converting into the right type of vector
	sf::Vector2u tempSize = window->getSize();
	sf::Vector2f windowSize(tempSize.x, tempSize.y);
	//Draw the grass
	sf::RectangleShape grass(windowSize);
	//Set grass position and color
	grass.setPosition(0, windowSize.y / 2);
	grass.setFillColor(sf::Color::Color(67, 157, 14, 255));
	window->draw(grass);

	//Find sprite
	//pan to right part of 
	//draw sprite
	window->draw(background);
}
