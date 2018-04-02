#include "stdafx.h"
#include "Object.h"

sf::Texture Object::SignTextures;
sf::Texture Object::CarTextures;


Object::Object()
{
}


Object::Object(sf::RenderWindow* w)
{
	window = w;
}


Object::Object(sf::RenderWindow* win, bool val)
{
	window = win;
	if (SignTextures.getSize().x == 0)
		SignTextures.loadFromFile("Pole Position sign sprites.png");
	int signVal = rand() % 19;

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


Object::~Object()
{
}


void Object::render(int carPos)
{
	int dist = position[1] - carPos;//distance to sign
	double mult = 300;//arbitrarily chosen, looks about right
	mult /= dist;//size is inversely proportional to distance
	if (mult > 0.05)//far too small
	{
		sprite.setPosition(mult*position[0] + 256, 216.5 + mult * 245);
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