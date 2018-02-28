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
	void drawRoad();

private:
	std::vector<double> roadCurve;
	sf::ConvexShape mainShape;
	sf::RenderWindow* windowPtr;
};

