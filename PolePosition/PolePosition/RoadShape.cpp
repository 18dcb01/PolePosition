#include "stdafx.h"
#include "RoadShape.h"


RoadShape::RoadShape(sf::RenderWindow  *window)
{
	this->setPointCount(4);
	//Define points.
	/*
	Taken from sfml doc page:
	The order in which you define the points is very important.
	They must all be defined either in clockwise
	or counter-clockwise order.
	If you define them in an inconsistent order,
	the shape will be constructed incorrectly.
	*/

	//Get dimensions of bottom of window.
	sf::Vector2u windowSize = window->getSize();

	//Firse point should be at bottom left of screen.
	this->setPoint(0, sf::Vector2f(0,windowSize.y));

	//Second point will be at bottom right of screen.
	this->setPoint(1, sf::Vector2f(windowSize.x,windowSize.y));
	//Third point will be a point with x coordnate equal to 
	// L/tan(45 degrees) where L is the height of the trapezoid or 1/10
	//The area of the screen and  is just L

	double trapezoidHeight = windowSize.x / 10.;
	double topPointOffset = trapezoidHeight / std::tan(45 * 3.14 / 180.0);
	this->setPoint(2,sf::Vector2f(topPointOffset, trapezoidHeight));
	//Point 4 is the same except it takes our previous values
	//minus overall screen dimensions.
	this->setPoint(3,sf::Vector2f(windowSize.x - topPointOffset, trapezoidHeight));
}

RoadShape::RoadShape(sf::Vector2f)
{
	//This is the same except it takes top of previous
	//trapezoid as base.
	this->setPointCount(4);
}


RoadShape::~RoadShape()
{
}

void RoadShape::setLean(int)
{
}
