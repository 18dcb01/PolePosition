#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>

//We need math lib for trig functions.

/*
	Defines the shape of the road and should provide scaling
	instances of itself to provide the illusion of distance.

	Should be an example of a trapezoid if road is straight.
	will default to being straigh will curve with functions.
	shoould lean one way or another if track is curving

	should be able to build base on either bottom of the screen
	or another RoadShape.
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

