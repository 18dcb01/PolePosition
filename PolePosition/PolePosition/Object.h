#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	virtual void render(int);
private:
	sf::Sprite sprite;
	int position[2];
};
