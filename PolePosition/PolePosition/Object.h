#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	~Object();

private:

	int position[2];
	sf::RectangleShape hitbox;
	//Sprite needs to be given a texture loaded
	//from a file in the constructor.
	sf::Sprite sprite;
};
