#include "stdafx.h"
<<<<<<< HEAD
#include "Racer.h"
=======
>>>>>>> 74fef943cb8d50f8de8e45ae904277b1a6f29050
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
<<<<<<< HEAD
}
=======

}
>>>>>>> 74fef943cb8d50f8de8e45ae904277b1a6f29050
