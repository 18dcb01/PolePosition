#include "stdafx.h"
#include "Racer.h"


//TODO: fix use of empty Racer constructer.
Racer::Racer(sf::RenderWindow* w, Road* roadAdr, Player * car, int color) : Car(w, color)
{
	carPtr = car;
	roadPtr = roadAdr;
	window = w;
	//Choose a random "enemy" sprite.
	initializeSprites(color);

	speed[0] = 0;
	speed[1] = 10;

	//Gets distance from player for scaling/ mapping purposes.
	xPlayerOffset = carPtr->getPosx() - position[0];
	yPlayerOffset = carPtr->getPosy() - position[1];
}

Racer::~Racer()
{

}

void Racer::Render(int j)
{
	if (!isOnScreen)
		return;

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
	//Check current scale and adjust hitbox.
	hitbox.setSize(sprite.getScale());
	//If car goes vertically off the bottom half of the screen,
	//Advance racer to next map segment.
	if (yPlayerOffset > window->getSize().x ||
		yPlayerOffset < -40)
		isOnScreen = false;

	/*
	if going to run into side of the road,
	Turn while keeping a constant speed.
	Defined in RACER_SPEED.
	*/
	sf::RectangleShape projectedPosition = hitbox;
	projectedPosition.setPosition(hitbox.getPosition().x + speed[0],
		hitbox.getPosition().y + speed[1]);
	//Loop so car will never crash.
	while (!(roadPtr->intersects(projectedPosition.getGlobalBounds())))
	{
		//Handle if going to crash into side of the road.
		//Adjust speed and direction accordingly.
	}
	//Check vertical and horozontal position.
	//alter scale if neccessary.
	//Borrow from sign code.
}


void Racer::setRoadRef(Road * ref)
{
	roadPtr = ref;
}
