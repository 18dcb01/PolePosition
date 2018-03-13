#pragma once
#include "Car.h"
class Racer : public Car
{
public:
	Racer();
	Racer(sf::RenderWindow*);
	Racer(int);
	~Racer();
	void tick();
private:
};