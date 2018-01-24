#pragma once
#include "Object.h"
#include <vector>
class Car :
	public Object
{
public:
	Car();
	~Car();

	void render();
private:
	//Differant position of car(turning).
	std::vector<sf::Sprite> sprites;
	int speed[2];
};

