#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>
#include "Direction.h"

//We need math lib for trig functions.

/*
	Defines the shape of the road and should provide scaling
	instances of itself to provide the illusion of distance.

	Should be an example of a trapezoid if road is straight.
	will default to being straight will curve with functions.
	shoould lean one way or another if track is curving

	should be able to build base on either bottom of the screen
	or another RoadShape.
*/
class RoadShape :
	public sf::ConvexShape
{
public:
	//Needs window to know the size of the bottom of the screen.
	RoadShape(sf::RenderWindow*, int);
	//Takes initial points from previous RoadShape.
	RoadShape(RoadShape, sf::RenderWindow*, int);
	~RoadShape();

	//Points...
	//Bottom left = 0
	//Bottom Right = 1
	//TopRight = 3
	//TopLeft = 2


	void setLean(Direction);

private:

};

