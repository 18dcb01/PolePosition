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


Object::~Object()
{
}


void Object::render(int)
{
}

<<<<<<< HEAD
=======

>>>>>>> origin/Words
void Object::setPos(int, int)
{
}

<<<<<<< HEAD
=======

>>>>>>> origin/Words
double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}