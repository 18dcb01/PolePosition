#include "stdafx.h"
#include "Object.h"

Object::Object(sf::RenderWindow* win)
{
	w = win;
}

Object::~Object()
{
}

void Object::render(int)
{
}

void Object::setPos(int, int)
{
}

double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}
