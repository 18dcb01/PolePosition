#include "stdafx.h"
#include "Racer.h"
#include "Racer.h"

Racer::Racer(sf::RenderWindow* w) : Car(sf::RenderWindow* w)
{
}

Racer::~Racer()
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

void Racer::tick()
{
}
