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
	Road();
	Road(sf::RenderWindow*, std::vector<double>);

	//everything in here
	void draw(double, double, double);

private:
	//drawing functions
	void drawRoad(double,int);
	void drawCenterLine(double, double, int);
	void drawOutsideLines(double, double);
	void drawThinLines(double, double);
	void resetLineHeight(std::vector<sf::ConvexShape>*);
	double getXVal(double, double);

	//variables
	std::vector<double> roadCurve;	//race track
	sf::RenderWindow* windowPtr;	//window
	std::vector<sf::ConvexShape> roadShape;	//main road
	std::vector<sf::ConvexShape> middleLine;	//center dotted line
	std::vector<sf::ConvexShape> littleLines;
	std::vector<sf::ConvexShape> stripedLine;	//red and white stripes
};

