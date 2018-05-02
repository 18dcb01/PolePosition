#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class Road
{
/*
TODO:

Should be the class that defines the quadratic that will represent the
curvature of the road.

 Uses road shapes to map sf objects to the aforementioned lines.

 moved loadTrack to road, plug it in
*/


public:
	Road();
	Road(sf::RenderWindow*);

	//everything in here
<<<<<<< HEAD
	void draw(double, double, double);
	double getXVal(double, double);

private:
	//drawing functions
	void calcRoad(double,int);
	void drawCenterLine(double, double, int);
	void drawOuterLine(double, double, int);
	void drawThinLines(double, double);
=======
	void draw();
	void edit(double, double, int);

private:
	//drawing functions
	void editRoad(double, double);
	void editCenterLine(double, double, int);
	void editOutsideLines(double, double);
	void editThinLines(double, double);
>>>>>>> Game-mechanics
	void resetLineHeight(std::vector<sf::ConvexShape>*);

	//utility functions
	void editX(std::vector<sf::ConvexShape>*, int, int, int);
	void editY(std::vector<sf::ConvexShape>*, int, int, int);
	void loadTrack();

	//variables
	std::vector<double> roadCurve;	//race track
	int lastTrackUsed;
	sf::Clock roadSpeedTimer;
	sf::RenderWindow* windowPtr;	//window
	std::vector<sf::ConvexShape> roadShape;	//main road
	std::vector<sf::ConvexShape> middleLine;	//center dotted line
	std::vector<sf::ConvexShape> littleLines;
	std::vector<sf::ConvexShape> stripedLine;	//red and white stripes
};

