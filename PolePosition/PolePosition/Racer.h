#pragma once
#include <iostream>
#include <stdexcept>
#include "Car.h"
#include "Road.h"

class Racer : public Car
{
public:
	Racer();
	Racer(sf::RenderWindow*, Road*,int);
	~Racer();
	void tick();
private:
	Road * roadPtr;
};