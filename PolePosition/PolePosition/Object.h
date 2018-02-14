#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object(sf::RenderWindow*);
	~Object();
	virtual void render(int);
	void setPos(int, int);
	double getPosx();
	double getPosy();

protected:
	sf::Sprite sprite;
	double position[2];
	sf::RenderWindow* w
};
