#pragma once
#include <iostream>
#include "Car.h"
#include "Road.h"

class Racer : public Car
{
public:
	Racer();
<<<<<<< HEAD
	Racer(sf::RenderWindow*, Road*);
=======
	Racer(sf::RenderWindow*, int);
	Racer(int);
>>>>>>> master
	~Racer();
	void tick();
private:
	Road * roadPtr;
};