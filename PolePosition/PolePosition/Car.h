#pragma once
#include "Object.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Car :
	public Object
{
public:
	Car();
	Car(sf::RenderWindow*, int);
	~Car();
	void initializeSprites(int);
	virtual void render(int);
	double getSpdx();
	double getSpdy();
	
protected:
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Sprite> spritesTwo;
	double speed[2];
	unsigned short spinny;
<<<<<<< HEAD
=======

	int crashing;
	bool isCrashing;

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
};