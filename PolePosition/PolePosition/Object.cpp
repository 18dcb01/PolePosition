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


double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}