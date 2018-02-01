#include "Game.h"
#include "stdafx.h"
#include "Game.h"

Game::Game(sf::RenderWindow *tempWindow)
{
	window = tempWindow;

	//creating background texture
	if (!background.loadFromFile("PolePositionMtFuji.png")
		cout << "Error loading background texture\n";
	//applying texture to background sprite
	backgroundSprite.setTexture(background);
	backgroundSprite.setScale(.5, .5);

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


//Draw road
void Game::drawMap()
{
	//Draw track pieces 5 at a time so user can see ahead.

	//3 possible track pieces.
	sf::ConvexShape straight();
	sf::ConvexShape veerRight();
	sf::ConvexShape veerLeft();
}


//drawing background and grass
void Game::drawBackground()
{
	//Grabbing window size and converting into the right type of vector
	sf::Vector2u tempSize = window->getSize();
	sf::Vector2f windowSize(tempSize.x, tempSize.y);


	//create background sprite
	backgroundSprite.setTexture(background);
	backgroundSprite.setScale(.5, .5);

	//rotate sprite to correct angle
	backgroundSprite.move(.1, 0);
	if (backgroundSprite.getPosition().x < -windowSize.x)
		backgroundSprite.setPosition(sf::Vector2f(0, 0));
	if (backgroundSprite.getPosition().x > 0)
		backgroundSprite.setPosition(sf::Vector2f(-windowSize.x, 0));

	//draw sprite
	window->draw(backgroundSprite);

	
	//Draw the grass
	sf::RectangleShape grass(windowSize);
	
	//Set grass position and color
	grass.setPosition(0, windowSize.y / 2);
	grass.setFillColor(sf::Color::Color(67, 157, 14, 255));
	window->draw(grass);
}
