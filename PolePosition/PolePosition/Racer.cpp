#include "stdafx.h"
<<<<<<< HEAD
#include "Racer.h"
=======
#include "Racer.h"

Racer::Racer() : Car()
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
>>>>>>> 803da4b1382250e8aef6ca4c31b47095e416d91a
