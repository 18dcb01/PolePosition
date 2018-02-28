#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <fstream>


Game::Game() :window(sf::VideoMode(512, 448), "Pole Position"), p(&window)
{
	tickCount = 0;
}


Game::~Game()
{
}


void Game::play()
{
	openingMenu();

	pState = GetKeyState(80);//log current p state for pauses

	//start vroom noises
	p.playSound();
	//qualifying round
	if (window.isOpen())
		race();

	//second race
	if (window.isOpen())
	{
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
		clock_t time = clock();
		//sfml overhead
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//should maybe get more complicated?
		if (GetKeyState(80) == pState)
		{
			p.playSound();
			tick();
		}
		else {
			p.pauseSound();
			render();
		}
		while (time > clock() - 20) {}
	}
	//A loop - continually calls tick
}


void Game::tick()
{
	tickCount++;
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
	p.drawDashboard();
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
	sf::RectangleShape grass(sf::Vector2f(width, tickCount%(height / 2)));
	//Set grass position and color
	grass.setPosition(0, height/2);
	grass.setFillColor(sf::Color::Green);
	window->draw(grass);
}


void Game::drawBackground()
{

}


void Game::openingMenu()
{
	sf::Texture t;
	t.loadFromFile("OpeningMenu.jpg");

	sf::Sprite s;
	s.setTexture(t);
	s.setScale(sf::Vector2f(.8, .8));

	sf::Sprite s2;
	s2.setTexture(t);
	s2.setScale(.8, .8);
	s2.setTextureRect(sf::IntRect(0, 0, 640, 80));
	s2.setPosition(0, 384);

	bool menuClosed = false;
	while (window.isOpen() && !menuClosed)
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
		window.draw(s);
		window.draw(s2);
		window.display();
	}
}