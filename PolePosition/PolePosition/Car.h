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
};