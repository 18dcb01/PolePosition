#include "stdafx.h"
#include "Racer.h"


Racer::Racer(sf::RenderWindow* w, Road* roadAdr, Player * car, int color) : Car(w, color)
{
	carPtr = car;
	roadPtr = roadAdr;
	window = w;

	//Will be modified later.
	position[0] = window->getSize().x / 2.;
	position[1] = window->getSize().y - 80;

	//sprite
	sprite = sprites.at(14);
	hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width,
		sprite.getGlobalBounds().height));

	sprite.setScale(1, 1);
	//Makes rectangle shape have a origin that matches up with
	//the sprite for transformations.
	double originX, originY;
	originX = hitbox.getSize().x / 2;
	originY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originX,originY);

	//For scale later.
	xReal = hitbox.getSize().x;
	yReal = hitbox.getSize().y;

	//For testing.
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color::Transparent);

	speed[0] = 0;
	speed[1] = 1;
	speedReal[0] = speed[0];
	speedReal[1] = speed[1];
	
	hitbox.setPosition(sf::Vector2f(position[0], position[1]));
	sprite.setPosition(position[0],position[1]);

	handleScaling();
	//Gets distance from player for scaling/ mapping purposes.
	xPlayerOffset = carPtr->getPosx() - position[0];
	yPlayerOffset = carPtr->getPosy() - position[1];
}

Racer::~Racer()
{

}

void Racer::render()
{
	int x = (speed[0] * 1.5) + 14;
	if (x < 3)
		x = 3;
	else if (x > 25)
		x = 25;
	sf::Sprite temp = sprite;
	sprite = sprites.at(x);
	sprite.setOrigin(temp.getOrigin());
	sprite.setPosition(temp.getPosition());
	sprite.setScale(temp.getScale());
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
		speed[0] = roadPtr->getCurrentRoadCurve();
		//std::cout << roadPtr->getCurrentRoadCurve() << '\n';
		//Update turn sprite texture.
		///Need to talk to Valerie about sprite stuff.

		//Update Sprite to show turning depending on speed[0].
		handleScaling();

		//If player crashes into a racer.
		if (hitbox.getGlobalBounds().intersects(carPtr->getHitbox().getGlobalBounds()))
		{
			std::cout << "Collision\n";
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
	//Will handle when the car catches up to the racer, needs polishing.
	speed[1] = speedReal[1] - (carPtr->getSpdy()) / 50.;
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
	double scalar = ((position[1] - window->getSize().y / 2) + 20) / 144;

	sprite.setScale(scalar * 2.5, scalar * 2.5);
	
	//Update hitbox size with scale factor used for sprite.
	hitbox.setSize(sf::Vector2f(xReal * scalar, yReal * scalar));

	double originX, originY;
	originX = hitbox.getSize().x / 2;
	originY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originX, originY);
	return;
}
