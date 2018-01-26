#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	~Object();
	virtual void render(int);
private:
	void setPos(int, int);
	int getPosx();
	int getPosy();

protected:
	sf::Sprite sprite;
	int position[2];
};
