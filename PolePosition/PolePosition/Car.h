#pragma once
#include "Object.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Car :
	public Object
{
public:
	Car();
	~Car();
	virtual void render(int);
protected:
	std::vector<sf::Sprite> sprites;
	int speed[2];
};

