#pragma once
#include "Car.h"
class Racer : public Car
{
public:
	Racer();
	Racer(int);
	~Racer();
	void tick();

private:
};