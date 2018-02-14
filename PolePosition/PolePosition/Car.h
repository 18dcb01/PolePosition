#pragma once
#include "Object.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Car :
	public Object
{
public:
	Car();
	Car(sf::RenderWindow*);
	~Car();
	virtual void render(int);
	double getSpdx();
	double getSpdy();

protected:
	std::vector<sf::Sprite> sprites;
	double speed[2];
};