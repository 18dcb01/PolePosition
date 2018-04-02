#pragma once
#include <iostream>
#include "Car.h"
#include "Road.h"

class Racer : public Car
{
public:
	Racer();
	Racer(sf::RenderWindow*, Road*);
	~Racer();
	void tick();
private:
	Road * roadPtr;
};