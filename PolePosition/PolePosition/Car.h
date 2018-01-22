#pragma once
#include "Object.h"
#include <vector>
class Car :
	public Object
{
public:
	Car();
	~Car();
	virtual void render(int);
private:
	std::vector<sf::Sprite> sprites;
	int speed[2];
};

