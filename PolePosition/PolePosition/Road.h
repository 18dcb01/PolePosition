#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class Road
{
/*
TODO:

Should be the class that defines the quadratic that will represent the
curvature of the road.

 Uses road shapes to map sf objects to the aforementioned lines.

*/


public:
	Road(sf::RenderWindow*, std::vector<double>);

	//everything in here
	void draw(double, double);

private:
	//drawing functions
	void drawRoad(double);
	void drawCenterLine(double, double);
	void drawOutsideLines(double, double);
	void drawThinLines(double, double);

	//variables
	std::vector<double> roadCurve;
	sf::RenderWindow* windowPtr;
	sf::Vector2f pointList[10];
	std::vector<sf::ConvexShape> roadShape;
};

