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
<<<<<<< HEAD
=======
  
     
	isCrashing = false;
	crashing = 0;
    
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
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
<<<<<<< HEAD
	for (int i = 1; i < 392; i += 65)
=======
  
	for (int i = 1; i < 392; i += 65)
     
	for (int i = 1; i < 457; i += 65)
    
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
	{
		s.setTextureRect(sf::IntRect(i, 257, 64, 31));
		sprites.push_back(s);
	}
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites.at(i).setOrigin(32, 15);
<<<<<<< HEAD
		//sprites.at(i).setPosition(256, 392);
=======
  
		//sprites.at(i).setPosition(256, 392);
     
    
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
		sprites.at(i).setScale(2, 2);
	}
	for (int i = 0; i < spritesTwo.size(); i++)
	{
		spritesTwo.at(i).setOrigin(32, 15);
		spritesTwo.at(i).setScale(2, 2);
	}
<<<<<<< HEAD

=======
  

     
    
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
}


Car::~Car()
{
}


//Should probably eventually be passed horizontal speed which is a double
void Car::render(int i)
{
<<<<<<< HEAD
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
=======
  
	int x = 0;
	if (!isCrashing)
	{
		x = (speed[0] * 1.5) + 14;
		if (x < 3)
			x = 3;
		else if (x > 25)
			x = 25;
		if (spinny < 32784)
			window->draw(sprites.at(x));
		else
			window->draw(spritesTwo.at(x));
	}
	else
	{
		if (crashing > 0)
		{
			if (crashing <= 6)
			{
				if (speed[0] > 0)
					x = 26 + (crashing / 3);
				else
					x = 2 - (crashing / 3);
			}
			else if (crashing <= 9)
			{
				x = 29;
				if (speed[0] < 0)
					x++;
			}
			else if (crashing <= 26)
				x = 31 + ((crashing - 12) / 3);
			else if (crashing > 26)
			{
				crashing = -50;
				speed[0] = 0;
				speed[1] = 0;
			}
		}
		else if (crashing < 0)
		{
			if (crashing < -1)
			{
				if (crashing % 8 != 0)
					x = 36;
				else
					x = 14;
				speed[0] = 0;
				speed[1] = 0;
			}
			else if (crashing == -1)
			{
				isCrashing = false;
				position[0] = 0;
				x = 14;
			}
		}
		crashing++;
		window->draw(sprites.at(x));
	}
    
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
}


double Car::getSpdx()
{
	return speed[0];
}


double Car::getSpdy()
{
	return speed[1];
}
