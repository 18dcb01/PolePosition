#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	//Maybe grab a pointer to the render window
}


Object::Object(sf::RenderWindow* win)
{
	window = win;
}


Object::Object(sf::RenderWindow* win, bool val)
{
	window = win;
	if (SignTextures.getSize().x == 0)
		SignTextures.loadFromFile("Pole Position sign sprites.png");
	sprite.setTexture(SignTextures);
	sprite.setPosition(0, 0);
	window->draw(sprite);
	window->display();
	int signVal = rand() % 16;
}


Object::~Object()
{
}


void Object::render(int carPos)
{
	sprite.setTexture(SignTextures);
	sprite.setPosition(0,0);
	window->draw(sprite);
}


void Object::setPos(int x, int y)
{
	position[0] = x;
	position[1] = y;
}


double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}