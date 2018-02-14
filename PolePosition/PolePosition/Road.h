#pragma once
#include <vector>
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
	Road(sf::RenderWindow*);
	void drawCurve();
	void drawRoad();

private:
	std::vector<double> road;
	sf::VertexArray roadSide;
	std::vector<sf::ConvexShape> roadShapes;
};

