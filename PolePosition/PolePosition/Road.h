#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class Road
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
/*
TODO:

Should be the class that defines the quadratic that will represent the
curvature of the road.

 Uses road shapes to map sf objects to the aforementioned lines.

*/


>>>>>>> fc81bf19fbd077c959e533a6ea64efaafa70a835
>>>>>>> b2b451e6475b28bede0a1c28672ac5e129f06b91
>>>>>>> 81229a37d76ac4b009bf655f8cb7923bc00906ce
public:
	Road();
	Road(sf::RenderWindow*, std::vector<double>);

	//everything in here
	void draw(double, double);

private:
	//drawing functions
	void drawRoad(double);
	void drawCenterLine(double, double);
	void drawOutsideLines(double, double);
	void drawThinLines(double, double);
	void resetLineHeight(std::vector<sf::ConvexShape>*);

	//variables
	std::vector<double> roadCurve;	//race track
	sf::RenderWindow* windowPtr;	//window
	std::vector<sf::ConvexShape> roadShape;	//main road
	std::vector<sf::ConvexShape> middleLine;	//center dotted line
	std::vector<sf::ConvexShape> littleLines;
	std::vector<sf::ConvexShape> stripedLine;	//red and white stripes
};

