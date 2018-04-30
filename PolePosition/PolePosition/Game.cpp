#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

Game::Game(sf::RenderWindow *w): p(w,&tickCount)
{
	srand(std::time(NULL));

	tickCount = 0;

	window = w;

	loadObjects();

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

	//Map is initialized to all straight for now.
	loadTrack();

	road = Road(w, map);
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

	//run start sign
	clock_t time = clock();
	int nextState = 0;
	while (window->isOpen()&&time>clock()-4000)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		render();

		//advance light
		if (time <= clock() - 1000 * nextState)
		{
			char str[11] = "start0.png";
			str[5] += nextState;
			signs.at(0).setTexture(str);
			nextState++;
		}
	}

	//qualifying round
	if (window->isOpen())
		race();

	//second race
	if (window->isOpen())
	{
		for (int i = 0; i < 7; i++)
			r[i] = Racer(window);
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
	road.draw(100, p.getSpdy(), p.getPosy());

	//Then signs, racers, and the player

	for (int i = 0; i < signs.size(); i++)
		signs.at(i).render(p.getPosy());

	p.render(14);

	if (GetKeyState(80) != pState)
		drawPause();
	window->display();

}


//drawing background and grass
void Game::drawBackground()
{
	//Grabbing window size and converting into the right type of vector
	sf::Vector2f windowSize = window->getView().getSize();


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
	pauseText.setPosition(sf::Vector2f(216, 240));//middle
	pauseText.setCharacterSize(16);
	pauseText.setFillColor(sf::Color(255, 250, 103));//yellowish
	window->draw(pauseText);
}


void Game::loadTrack()
{
	//open stream
	std::fstream stream;
	stream.open("Basic Track.txt", std::ios::in);
	std::string str;

	//import tract into vector
	while (getline(stream, str))
	{
		map.push_back(stod(str));
	}
	//make sure the map isnt empty
	if (map.size() == 0)
		map.push_back(0);
}

void Game::loadObjects()
{

	Object start(window, "Start0.png");
	start.setPos(50, 0);
	signs.push_back(start);
	signs.at(0).setTexture("Start0.png");

	for (int i = 1; i < 100; i++)
	{
		Object obj(window, &road);
		obj.setPos(rand() % 2 == 0 ? -30 : 130, 15000 * i);
		signs.push_back(obj);
	}

	Object namco(window, "Namco.png");
	namco.setPos(50, 20000);
	signs.push_back(namco);
	signs.back().assignTexture();
}
