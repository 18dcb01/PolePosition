#include "stdafx.h"
#include "Object.h"

sf::Texture Object::SignTextures;
sf::Texture Object::CarTextures;


Object::Object()
{
	//Maybe grab a pointer to the render window
}


Object::Object(sf::RenderWindow* win)
{
	window = win;
}


Object::Object(sf::RenderWindow* win, bool val)
{
	window = win;
	if (SignTextures.getSize().x == 0)
		SignTextures.loadFromFile("Pole Position sign sprites.png");
	int signVal = rand() % 16;
	sprite.setTextureRect(sf::IntRect(signVal * 96, 0, 95, 72));
	sprite.setOrigin(48, 72);
	sprite.setTexture(SignTextures);
}


Object::~Object()
{
}


void Object::render(int carPos)
{
	int dist = position[1] - carPos;//distance to sign
	double mult = 300;//randomly chosen to start
	mult /= dist;//size is inversely proportional to distance
	if (mult > 0.05)//far too small
	{
		sprite.setPosition(mult*position[0] + 256, 203 + mult * 245);
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