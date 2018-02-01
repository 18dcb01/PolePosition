#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::render(int)
{
}

<<<<<<< HEAD
void Object::setPos(int, int)
{
}

int Object::getPosx()
{
	return 0;
}

int Object::getPosy()
{
	return 0;
}
=======

double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}
>>>>>>> 74fef943cb8d50f8de8e45ae904277b1a6f29050
