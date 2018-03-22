#include "stdafx.h"
#include "Racer.h"


Racer::Racer()
{
}


Racer::Racer(sf::RenderWindow* w) : Car(w)
{
}

Racer::Racer(int pos)
{
	if (pos % 2 == 0)
		position[0] = -20;
	else
		position[0] = 20;
	position[1] = -20 * (pos / 2);
}

Racer::~Racer()
{

}

void Racer::tick()
{
}