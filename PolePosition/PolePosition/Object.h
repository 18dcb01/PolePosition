#pragma once
#include <SFML\Graphics.hpp>
#include "Road.h"

class Object
{
public:
	Object();
	Object(sf::RenderWindow *, Road*);
	Object(sf::RenderWindow * w, int i);
	Object(sf::RenderWindow *);
	Object(sf::RenderWindow *, const char[]);
	~Object();
	virtual void render(int);
	void setPos(int, int);
	double getPosx();
	double getPosy();
	void assignTexture();
	void setTexture(const char[]);

protected:
	static sf::Texture SignTextures;
	static sf::Texture CarTextures;
	sf::Texture localTexture;
	sf::Sprite sprite;
	double position[2];
	sf::RenderWindow* window;

	sf::RectangleShape hitbox;//for collisions
	static Road* road;//need to see the road for reference
};
