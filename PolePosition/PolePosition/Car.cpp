#include "stdafx.h"
#include "Car.h"


Car::Car(sf::RenderWindow* w) : Object(sf::RenderWindow* w)
{
}


Car::~Car()
{
}

void Car::render(int)
{
}


double Car::getSpdx()
{
	return speed[0];
}


double Car::getSpdy()
{
	return speed[1];
}