#include "stdafx.h"
#include "RoadShape.h"


RoadShape::RoadShape(sf::RenderWindow  *window, int screenNum)
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

	//Denominator of trapezoid height is dependent on how many road pieces
	//are on the screen.
	double trapezoidHeight = windowSize.x / (2 * screenNum);
	double topPointOffset = trapezoidHeight / std::tan(45 * 3.14 / 180.0);


	//Point 3 is the same as below except it takes our previous values
	//minus overall screen dimensions.
	this->setPoint(2, sf::Vector2f(windowSize.x - topPointOffset, trapezoidHeight));

	/*
	Fourth point will be a point with x coordnate equal to 
	L/tan(45 degrees) where L is the height of the trapezoid or 
	1/( 2 times number of road pieces on screen).
	The area of the screen and  is just L.
	*/
	this->setPoint(3,sf::Vector2f(topPointOffset, trapezoidHeight));
	
}

RoadShape::RoadShape(RoadShape previous, sf::RenderWindow *window, int screenNum)
{
	//This is the same except it takes top of previous
	//trapezoid as base.
	this->setPointCount(4);

	sf::Vector2f topLeftPrevious = previous.getPoint(3);
	sf::Vector2f topRightPrevious = previous.getPoint(2);


	//First point should be top left of previous.
	this->setPoint(0, topLeftPrevious);
	//Second point should be top right of previous.
	this->setPoint(1, topRightPrevious);

	sf::Vector2u windowSize = window->getSize();

	//Trapezoid height
	double trapezoidHeight = (windowSize.x / (2 * screenNum));
	double topPointOffset = trapezoidHeight / std::tan(45 * 3.14 / 180);
	//Point 3
	this->setPoint(2, sf::Vector2f(topRightPrevious.x - topPointOffset, trapezoidHeight + topRightPrevious.y));

	/*
	Fourth point will be a point with x coordnate equal to
	L/tan(45 degrees) where L is the height of the trapezoid or
	1/( 2 times number of road pieces on screen).
	The area of the screen and  is just L.
	*/
	this->setPoint(3,sf::Vector2f(topPointOffset,trapezoidHeight + topRightPrevious.y));
}


RoadShape::~RoadShape()
{
}

void RoadShape::setLean(Direction)
{
	//Points...
	//Bottom left = 0
	//Bottom Right = 1
	//TopRight = 3
	//TopLeft = 2

}

