#include "stdafx.h"
#include "Racer.h"


Racer::Racer()
{
}


Racer::Racer(sf::RenderWindow* w, Road* roadAdr, int color) : Car(w, color)
{
	roadPtr = roadAdr;
	window = w;
	//Choose a random "enemy" sprite.
	initializeSprites(color);
}

Racer::~Racer()
{

}

void Racer::tick()
{
	//Check current scale an adjust hitbox.
	hitbox.setSize(sprite.getScale());
	//If out of bounds, destroy car.

	//if (!(roadPtr->intersects(hitbox.getGlobalBounds())))
	//{
		//destroy car.
	//	std::cout << "boom\n";
	//}
	//Check vertical and horozontal position.
	//alter scale if neccessary.
	//Borrow from sign code.

	//If is about to crash, alter course
	//will need access to road as well as overall map.
}