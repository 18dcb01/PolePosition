#include "stdafx.h"
#include "Racer.h"


//TODO: fix use of empty Racer constructer.
Racer::Racer(sf::RenderWindow* w, Road* roadAdr, Player * car, int color) : Car(w, color)
{
	carPtr = car;
	roadPtr = roadAdr;
	window = w;

	//Will be modified later.
	position[0] = window->getSize().x / 2.;
	position[1] = window->getSize().y - 80;

	//Choose a random "enemy" sprite.
	//initializeSprites(color);
	sprite = sf::Sprite(sprites.at(6));
	hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width,
		sprite.getGlobalBounds().height));

	//For scale later.
	xReal = hitbox.getSize().x;
	yReal = hitbox.getSize().y;

	//For testing.
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color::Transparent);

	speed[0] = 0;
	speed[1] = 1;
	
	hitbox.setPosition(sf::Vector2f(position[0], position[1]));
	sprite.setPosition(position[0],position[1]);

	//Gets distance from player for scaling/ mapping purposes.
	xPlayerOffset = carPtr->getPosx() - position[0];
	yPlayerOffset = carPtr->getPosy() - position[1];
}

Racer::~Racer()
{

}

void Racer::render()
{
	if (isOnScreen)
	{
		//within the draw space
		window->draw(sprite);
		window->draw(hitbox);
	}
}


void Racer::tick()
{
	//Works
	isOnScreen = position[1] < window->getSize().y &&
		position[1] > window->getSize().y/2;

	if (isOnScreen)
	{
		//Update speed[0] to adjust for road turning.
		speed[0] = roadPtr->getCurrentRoadCurve();

		//Update turn sprite texture.
		///Need to talk to Valerie about sprite stuff.
		sprite.setTexture(*sprites.at((int)speed[0]).getTexture());

		//Update Sprite to show turning depending on speed[0].
		handleScaling();

		//If player crashes into a racer.
		if (hitbox.getGlobalBounds().intersects(carPtr->getHitbox().getGlobalBounds()) &&
			yPlayerOffset == 0)
		{
			//Explode racer.
		}

	}

	updateEntitys();	
}


void Racer::setRoadRef(Road * ref)
{
	roadPtr = ref;
}

void Racer::updateEntitys()
{
	position[0] += speed[0];
	position[1] -= speed[1];

	hitbox.setPosition(position[0], position[1]);
	sprite.setPosition(hitbox.getPosition());
	//Gets distance from player for scaling/ mapping purposes.
	xPlayerOffset = carPtr->getPosx() - position[0];
	yPlayerOffset = carPtr->getPosy() - position[1];

	return;
}

void Racer::handleScaling()
{
	
	//Make distance from 'camera' a percentage that we can use in a scale factor.
	//Distance to middle of screen.
	double scalar = (position[1] - window->getSize().y / 2) / 144;
	sprite.setScale(scalar * 2.5, scalar * 2.5);
	
	//Update hitbox size with scale factor used for sprite.
	hitbox.setSize(sf::Vector2f(xReal * scalar, yReal * scalar));
	return;
}
