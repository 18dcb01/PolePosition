#include "stdafx.h"
#include "Car.h"
#include <iostream>


Car::Car() : Object()
{
}


//Will need to get a variable to determine color
Car::Car(sf::RenderWindow* w, int color) : Object(w)
{
	if (CarTextures.getSize().x == 0)
		CarTextures.loadFromFile("CarTextures.png");
	initializeSprites(color % 4);
	spinny = 0;
}


//The int that's passed in will determine the car's color
//It's not currently being used, but will need to be implemented
void Car::initializeSprites(int x)
{
	int offset = x * 64;
	sf::Sprite s(CarTextures);
	s.setPosition(256, 392);
	for (int i = 911; i > 65; i -= 65)
	{
		s.setTextureRect(sf::IntRect(i, 33 + offset, 64, 31));
		sprites.push_back(s);
		s.setTextureRect(sf::IntRect(i, 321 + offset, 64, 31));
		spritesTwo.push_back(s);
	}
	for (int i = 1; i < 912; i += 65)
	{
		s.setTextureRect(sf::IntRect(i, 1 + offset, 64, 31));
		sprites.push_back(s);
		s.setTextureRect(sf::IntRect(i, 289 + offset, 64, 31));
		spritesTwo.push_back(s);
	}
	for (int i = 1; i < 392; i += 65)
	{
		s.setTextureRect(sf::IntRect(i, 257, 64, 31));
		sprites.push_back(s);
	}
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites.at(i).setOrigin(32, 15);
		//sprites.at(i).setPosition(256, 392);
		sprites.at(i).setScale(2, 2);
	}
	for (int i = 0; i < spritesTwo.size(); i++)
	{
		spritesTwo.at(i).setOrigin(32, 15);
		spritesTwo.at(i).setScale(2, 2);
	}
}


Car::~Car()
{
}


//Should probably eventually be passed horizontal speed which is a double
void Car::render()
{
	int x = (speed[0] * 1.5) + 14;
	if (x < 3)
		x = 3;
	else if (x > 25)
		x = 25;
	//spinny += 50 * speed[1];
	if (spinny < 32784)
		window->draw(sprites.at(x));
	else
		window->draw(spritesTwo.at(x));
}


double Car::getSpdx()
{
	return speed[0];
}


double Car::getSpdy()
{
	return speed[1];
}