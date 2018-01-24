#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	position[0] = -1001;
	position[1] = -1001;
}

Object::~Object()
{
}

void Object::render(int)
{
}

void Object::setPos(int x, int y)
{
	position[0] = x;
	position[1] = y;

}

int Object::getPosx()
{
	return position[0];
}

int Object::getPosy()
{
	return position[1];
}
