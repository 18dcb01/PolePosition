#pragma once
#include "Object.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Car :
	public Object
{
public:
	Car();
<<<<<<< HEAD
	Car(sf::RenderWindow * w);
=======
	Car(sf::RenderWindow*, int);
>>>>>>> Game-mechanics
	~Car();
	void initializeSprites(int);
	virtual void render();
	double getSpdx();
	double getSpdy();
	void setSpdx(double);
	void setSpdy(double);

protected:
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Sprite> spritesTwo;
	double speed[2];
	unsigned short spinny;
	int crashing;
	bool isCrashing;
};