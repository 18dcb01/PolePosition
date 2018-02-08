#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>

//We need math lib for trig functions.

/*
	Should be a piece of the larger road that maps itself to lines
	drawn previously in Road.
*/
class RoadShape :
	public sf::ConvexShape
{
public:
	//Needs window to know the size of the bottom of the screen.
	RoadShape(sf::RenderWindow*);
	//Takes initial points from previous RoadShape.
	RoadShape(sf::Vector2f, sf::Vector2f, sf::RenderWindow*);
	~RoadShape();
	void setLean(int);

private:

};

