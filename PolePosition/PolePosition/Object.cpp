#include "stdafx.h"
#include "Object.h"
#include "Road.h"

sf::Texture Object::SignTextures;
sf::Texture Object::CarTextures;

Road* Object::road;

Object::Object()
{
}


Object::Object(sf::RenderWindow* w)
{
	window = w;
}

Object::Object(sf::RenderWindow * w, const char fileName[])
{
	window = w;

	localTexture.loadFromFile(fileName);
	sprite.setOrigin(localTexture.getSize().x / 2, localTexture.getSize().y);
}


Object::Object(sf::RenderWindow* w, Road * r)
{
	window = w;
	road = r;

	//if textures are unloaded, load them
	if (SignTextures.getSize().x == 0)
		SignTextures.loadFromFile("Pole Position sign sprites.png");

	int signVal = rand() % 19;
	while (signVal == 6 || signVal == 7 || signVal == 14 || signVal == 15)
	{
		signVal = rand() % 19;
	}

	if (signVal < 16)
	{
		sprite.setTextureRect(sf::IntRect(signVal * 96, 0, 95, 78));
		sprite.setOrigin(48, 78);
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(signVal * 128 - 512, 32, 127, 46));
		sprite.setOrigin(64, 46);
	}
	sprite.setTexture(SignTextures);

	
}


Object::Object(sf::RenderWindow * w, int i)
{
	window = w;

	sprite.setTextureRect(sf::IntRect(i * 96, 0, 95, 78));
	sprite.setOrigin(48, 78);
}


Object::~Object()
{
}


void Object::render(int carPos)
{
	int dist = position[1] - carPos+1100;//distance to sign
	double mult = 900;//arbitrarily chosen, looks about right
	mult /= dist;//size is inversely proportional to distance
	double ypos = 199 + mult * 245;
	if (mult > 0.05)//far too small
	{
		sprite.setPosition(road->getXVal(ypos,position[0]/100.0),ypos);
		sprite.setScale(2 * mult, 2 * mult);//looks better?
		if (sprite.getPosition().y > 224 && sprite.getPosition().y < 800)//within the draw space
			window->draw(sprite);
	}
}


void Object::setPos(int x, int y)
{
	position[0] = x;
	position[1] = y;
}


double Object::getPosx()
{
	return position[0];
}


double Object::getPosy()
{
	return position[1];
}


//reassign texture after copying
void Object::assignTexture()
{
	sprite.setTexture(localTexture);
}

void Object::setTexture(const char texture[])
{
	localTexture.loadFromFile(texture);
	sprite.setTexture(localTexture);
}
