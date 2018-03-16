#include "stdafx.h"
#include "Car.h"
#include <iostream>


Car::Car() : Object()
{
}


//Will need to get a variable to determine color
Car::Car(sf::RenderWindow* w) : Object(w)
{
	if (CarTextures.getSize().x == 0)
		CarTextures.loadFromFile("CarTextures.png");
	initializeSprites(0);
	sprites.at(0).setOrigin(32, 15);
	sprites.at(0).setPosition(256, 392);
	sprites.at(0).setScale(2, 2);
}


//The int that's passed in will determine the car's color
//It's not currently being used, but will need to be implemented
void Car::initializeSprites(int x)
{
	sf::Sprite s(CarTextures);

	for (int i = 911; i > 65; i -= 65)
	{
		s.setTextureRect(sf::IntRect(i, 33, 64, 31));
		sprites.push_back(s);
	}
	for (int i = 1; i < 912; i += 65)
	{
		s.setTextureRect(sf::IntRect(i, 1, 64, 31));
		sprites.push_back(s);
	}
	for (int i = 1; i < 327; i += 65)
	{
		s.setTextureRect(sf::IntRect(i, 257, 64, 31));
		sprites.push_back(s);
	}
}


Car::~Car()
{
}


//Should probably eventually be passed horizontal speed which is a double
void Car::render(int i)
{
	window->draw(sprites.at(i));
}


double Car::getSpdx()
{
	return speed[0];
}


double Car::getSpdy()
{
	return speed[1];
}