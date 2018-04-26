#include "stdafx.h"
#include "Racer.h"


//TODO: fix use of empty Racer constructer.
Racer::Racer(sf::RenderWindow* w, Road* roadAdr, Player * car, int color) : Car(w, color)
{
	carPtr = car;
	roadPtr = roadAdr;
	window = w;

	position[0] = window->getSize().x / 2.;
	position[1] = window->getSize().y - 80;
	//Choose a random "enemy" sprite.
	initializeSprites(color);
	sprite = sf::Sprite(sprites.at(6));

	hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width,
		sprite.getGlobalBounds().height));
	xRealHeight = hitbox.getSize().x;
	yRealHeight = hitbox.getSize().y;
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color::Transparent);

	speed[0] = 0;
	speed[1] = 1;
	
	hitbox.setPosition(sf::Vector2f(position[0], position[1]));
	sprite.setPosition(hitbox.getPosition());
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
	
	//Check current scale and adjust hitbox.
	//hitbox.setScale(sprite.getScale());

	//Works
	isOnScreen = position[1] < window->getSize().y &&
		position[1] > window->getSize().y/2;

	if (isOnScreen)
	{
		//Update speed[0] to adjust for road turning.
		//speed[0] = roadPtr->getCurrentRoadCurve();
		//Update Sprite to show turning depending on speed[0].
		handleScaling();

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
	//Print distance to middle of screen.
	std::cout << position[1] - window->getSize().y/2 << std::endl;
	//Mathmatically determine scale.
	return;
}
