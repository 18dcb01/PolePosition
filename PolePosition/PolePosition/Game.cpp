#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

Game::Game(sf::RenderWindow *w): p(w, &tickCount, 3)
{
	tickCount = 0;
	for (int i = 0; i < 500; i++)
	{
		Object obj(w, true);
		obj.setPos(-300, 15000*i);
		signs.push_back(obj);
	}

	window = w;

	//creating background texture
	if (!background.loadFromFile("PolePositionMtFuji.png"))
	{
		std::cout << "Error loading background texture\n";
	}
	else
	{
		//applying texture to background sprite
		backgroundSprite.setTexture(background);
	}

	road = Road(w);
}


Game::~Game()
{
}


void Game::play()
{
	openingMenu();

	pState = GetKeyState(80);//log current p state for pauses
	if (pState < 0)
		pState += 128;

	//start vroom noises
	p.playSound();
	//qualifying round
	if (window->isOpen())
		race();

	//second race
	if (window->isOpen())
	{
		for (int i = 0; i < 7; i++)
			r[i] = Racer(window, 0);
		race();
	}
	//Calls race (twice bc two races)
	tick();
}


void Game::race()
{
	while (window->isOpen())
	{
		clock_t time = clock();
		//sfml overhead
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
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
	render();
}


void Game::render()
{
	window->clear();
	
	//First, drawBackground
	drawBackground();
	p.drawDashboard(GetKeyState(80) != pState);

	//Draw Road
	road.edit(-p.getPosx() * (p.getSpdy() / 50), p.getSpdy(), 10);
	road.draw();

	//Then signs, racers, and the player
	if (GetKeyState(80) != pState)
		drawPause();
	p.render();

	for (int i = 0; i < signs.size(); i++)
		signs.at(i).render(p.getPosy());
	window->display();

}


//drawing background and grass
void Game::drawBackground()
{
	//Grabbing window size and converting into the right type of vector
	sf::Vector2u tempSize = window->getSize();
	sf::Vector2f windowSize(tempSize.x, tempSize.y);


	//create background sprite
	backgroundSprite.setScale(1, 1.75);

	//rotate sprite to correct angle
	backgroundSprite.move(-.001, 0);
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
	while (window->isOpen() && !menuClosed)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
				menuClosed = true;
		}
		window->clear();
		window->draw(s);
		window->draw(s2);
		window->display();
	}
}

void Game::drawPause()
{
	sf::Font aClassic;

	if (!aClassic.loadFromFile("Arcade Classic.ttf"))
	{
		std::cout << "Didn't work dude" << std::endl;
	}

	sf::Text pauseText;
	pauseText.setFont(aClassic);
	pauseText.setString("PAUSE");
	pauseText.setPosition(sf::Vector2f(216, 240));
	pauseText.setCharacterSize(16);
	pauseText.setFillColor(sf::Color(255, 250, 103));
	window->draw(pauseText);
}