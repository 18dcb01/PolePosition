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

void Racer::Render(int j)
{
	int x = (speed[0] * 1.5) + 14;
	if (x < 3)
		x = 3;
	else if (x > 25)
		x = 25;
	spinny += 50 * speed[1];
	if (spinny < 32784)
		window->draw(sprites.at(x));
	else
		window->draw(spritesTwo.at(x));
	return;
}


void Racer::tick()
{
	//Check current scale an adjust hitbox.
	hitbox.setSize(sprite.getScale());
	//If car goes vertically off the bottom half of the screen,
	//Advance racer to next map segment.

	//If out of bounds, destroy car.
	if (!(roadPtr->intersects(hitbox.getGlobalBounds())))
	{
		//destroy car.
		//std::cout << "boom\n";
	}
	
	//Check vertical and horozontal position.
	//alter scale if neccessary.
	//Borrow from sign code.

	//If is about to crash, alter course
	//will need access to road as well as overall map.
}


void Racer::setRoadRef(Road * ref)
{
	roadPtr = ref;
}
