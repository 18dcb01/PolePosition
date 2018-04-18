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
	if (isOnScreen)//within the draw space
		window->draw(sprite);

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

	double speedVector = std::sqrt(std::pow(speed[0], 2) + std::pow(speed[1], 2));

	//Handle if going to crash into side of the road.
	//Adjust speed and direction accordingly.
	//Loop so car will never crash.
	//Also keep total velocity of ten.
	while (!(roadPtr->intersects(projectedPosition.getGlobalBounds())) ||
			speedVector != RACER_SPEED)
	{
		//Update position after adjustments.
		projectedPosition.setPosition(hitbox.getPosition().x + speed[0],
			hitbox.getPosition().y + speed[1]);
		//Update speed vector.
		speedVector = std::sqrt(std::pow(speed[0], 2) + std::pow(speed[1], 2));

		//If projected position is less than RoadShapes xPos, turn right.
		if (projectedPosition.getPosition().x 
			< roadPtr->getRelativeBounds(projectedPosition.getPosition())
			.getLocalBounds().left)
		{
			speed[0] -= 1;
		}
		//If projected position is greater than RoadShape's xPos, turn left.
		else if (projectedPosition.getPosition().x
			< roadPtr->getRelativeBounds(projectedPosition.getPosition())
			.getLocalBounds().left)
		{
			speed[0] += 1;
		}
		//Based on pythagorean thing.
		//Update y speed to keep vector.
		speed[1] = std::sqrt(std::pow(RACER_SPEED,2) - std::pow(speed[0],2) );
	}
	//Update Sprite to show turning depending on speed[1].


	//Check vertical and horozontal position.
	//alter scale if neccessary.
	//Borrow from sign code.
	int dist = yPlayerOffset;
	double mult = 1000;//arbitrarily chosen, looks about right
	mult /= yPlayerOffset;//size is inversely proportional to distance
	if (mult > 0.05)//far too small
	{
		//sprite.setPosition(mult*position[0] + 256, 216.5 + mult * 245);
		sprite.setScale(2 * mult, 2 * mult);//looks better?
	}
}


void Racer::setRoadRef(Road * ref)
{
	roadPtr = ref;
}
