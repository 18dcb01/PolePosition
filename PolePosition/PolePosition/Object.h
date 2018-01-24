#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	~Object();
	virtual void render(int);
protected:
	sf::Sprite sprite;
	int position[2];
};
