#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	Object(sf::RenderWindow*);
	Object(sf::RenderWindow *, bool);
	~Object();
	virtual void render(int);
	void setPos(int, int);
	double getPosx();
	double getPosy();

protected:
	static sf::Texture SignTextures;
	static sf::Texture CarTextures;
	sf::Sprite sprite;
	double position[2];
	sf::RenderWindow* window;
	sf::RectangleShape hitbox;
};
