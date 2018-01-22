#pragma once
class Object
{
public:
	virtual void render(int);
private:
	sf::Sprite sprite;
	int position[2];
};
