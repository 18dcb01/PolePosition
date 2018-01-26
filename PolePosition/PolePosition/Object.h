#pragma once
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	~Object();
	virtual void render(int);
<<<<<<< HEAD
private:
=======
	void setPos(int, int);
	int getPosx();
	int getPosy();

protected:
>>>>>>> 803da4b1382250e8aef6ca4c31b47095e416d91a
	sf::Sprite sprite;
	int position[2];
};
