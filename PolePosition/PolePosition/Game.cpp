#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>

Game::Game():window(sf::VideoMode(512,448), "Pole Position")
{
	//Probably something else we should be doing here
}


Game::~Game()
{

}


void Game::play()
{
	//menu
	sf::Texture menuTexture;
	menuTexture.loadFromFile("OpeningMenu.jpg");

	sf::Sprite menu;
	menu.setTexture(menuTexture);
	menu.setScale(sf::Vector2f(.8, .8));

	sf::Sprite bar;//the bar at the bottom, is naturally not filled in
	bar.setTexture(menuTexture);
	bar.setScale(.8, .8);
	bar.setTextureRect(sf::IntRect(0, 0, 640, 80));//a part of the texture that is pure tan
	bar.setPosition(0, 384);

	bool menuClosed = false;
	while (window.isOpen()&&!menuClosed)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				menuClosed = true;
		}
		window.clear();

		window.draw(menu);
		window.draw(bar);

		window.display();
	}
	origPState = GetKeyState(80);//check what state the P is in
	if (origPState < -5)//if p was pressed
		origPState += 128;//get what will happen when it is unpressed

	//proceed to game
	p.playSound();//vroom
	//qualifying round
	if (window.isOpen())
		race();

	//second race
	if (window.isOpen())
	{
		for (int i = 0; i < 7; i++)
			r[i] = Racer(i);
		race();
	}
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
		if(GetKeyState(80)==origPState)//if not paused
			tick();
		else
		{
			int i;//looks like it just says pause
		}

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
	window.clear();
	//First, drawBackground
	drawBackground();
	//Then, drawMap
	drawMap(&window);
	//Then signs, racers, and the player
	window.display();

}


void Game::drawMap(sf::RenderWindow *window)
{
	//this all needs to go into a vector dummy
	sf::Vector2u windowSize = window->getSize();
	int width = windowSize.x;
	int height = windowSize.y;
	//Draw the grass
	sf::RectangleShape grass(sf::Vector2f(width, rand()%(height / 2)));//random for testing
	//Set grass position and color
	grass.setPosition(0, height/2);
	grass.setFillColor(sf::Color::Green);
	window->draw(grass);
}


void Game::drawBackground()
{

}
