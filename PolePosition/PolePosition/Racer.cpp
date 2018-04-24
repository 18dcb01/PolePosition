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
	//initializeSprites(color);
	hitbox.setSize(sf::Vector2f(10,10));
	hitbox.setOutlineThickness(5);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color::Transparent);

	speed[0] = 1;
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
		//window->draw(sprite);
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
		/*
		if going to run into side of the road,
		Turn while keeping a constant speed.
		Defined in RACER_SPEED.
		*/
		sf::RectangleShape projectedPosition;
		projectedPosition = hitbox;
		projectedPosition.setPosition(position[0] + speed[0],
			position[1] - speed[1] - 5);

		double speedVector = std::sqrt(std::pow(speed[0], 2) + std::pow(speed[1], 2));

		std::cout << (roadPtr->intersects(projectedPosition.getGlobalBounds())) << std::endl;
		//fix
		if(!(roadPtr->intersects(projectedPosition.getGlobalBounds())))
			preventCrash(&speedVector,&projectedPosition);

		//Update Sprite to show turning depending on speed[1].


		//Check vertical and horozontal position.
		//alter scale if neccessary.
		//Borrow from sign code.
		xPlayerOffset = carPtr->getPosx() - position[0];
		yPlayerOffset = carPtr->getPosy() - position[1];

		int dist = yPlayerOffset;
		double mult = 1000;//arbitrarily chosen, looks about right
		mult /= yPlayerOffset;//size is inversely proportional to distance
		if (mult > 0.05)//far too small
		{
			sprite.setPosition(mult*position[0] + 256, 216.5 + mult * 245);
			sprite.setScale(2 * mult, 2 * mult);//looks better?
		}
	}

	//TODO: make game render Racers in meaningful way.
	updateEntitys();
}


void Racer::setRoadRef(Road * ref)
{
	roadPtr = ref;
}

void Racer::preventCrash(double * vector, sf::RectangleShape * projected)
{
	//Handle if going to crash into side of the road.
	//Adjust speed and direction accordingly.
	//Loop so car will never crash.
	//Also keep total velocity of ten.
	while (!(roadPtr->intersects(projected->getGlobalBounds())) )
	{
		//If projected position is less than RoadShapes xPos, turn right.
		if (projected->getPosition().x
			< roadPtr->getRelativeBounds(projected->getPosition())
			.getLocalBounds().left)
		{
			speed[0]+= 0.01;
		}
		//If projected position is greater than RoadShape's xPos, turn left.
		else if (projected->getPosition().x
			< roadPtr->getRelativeBounds(projected->getPosition())
			.getLocalBounds().left)
		{
			speed[0]-= 0.01;
		}
		//Update position after adjustments.
		projected->setPosition(hitbox.getPosition().x + speed[0],
			hitbox.getPosition().y - speed[1]);

		//Based on pythagorean thing.
		//Update y speed to keep vector.
		//speed[1] = std::sqrt(std::pow(RACER_SPEED, 2) - std::pow(speed[0], 2));
		//Update speed vector.
		//*vector = std::sqrt(std::pow(speed[0], 2) + std::pow(speed[1], 2));

		std::cout << "XPos: " << projected->getPosition().x << " YPos: " << projected->getPosition().y << '\n';
	}
	return;
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
