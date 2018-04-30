#pragma once
#include <vector>
#include <iostream>
#include <math.h>
<<<<<<< HEAD
#include <stdexcept>
=======

#include <stdexcept>

#include <fstream>

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class Road
{
<<<<<<< HEAD
=======

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
/*

	The class that represents the road as a bunch of convex shapes
	and the surprisingly complex math needed to calculate each point.

*/


<<<<<<< HEAD
=======


>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
public:
	Road();
	Road(sf::RenderWindow*, std::vector<double>);

	//everything in here
<<<<<<< HEAD
	void draw(double, double);
	double getRoadSize();
	double getCurrentRoadCurve();
=======

	void draw(double, double);
	double getRoadSize();
	double getCurrentRoadCurve();


>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
	void draw();
	void edit(double, double, int);

private:
	//drawing functions
<<<<<<< HEAD
	void editRoad(double);
=======
	void editRoad(double, double);

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
	void editCenterLine(double, double, int);
	void editOutsideLines(double, double);
	void editThinLines(double, double);
	void resetLineHeight(std::vector<sf::ConvexShape>*);

	//utility functions
	void editX(std::vector<sf::ConvexShape>*, int, int, int);
	void editY(std::vector<sf::ConvexShape>*, int, int, int);
<<<<<<< HEAD
=======

	void loadTrack();
>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637

	//variables
	std::vector<double> roadCurve;	//race track
	int lastTrackUsed;
<<<<<<< HEAD
=======

	sf::Clock roadSpeedTimer;

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
	sf::RenderWindow* windowPtr;	//window
	std::vector<sf::ConvexShape> roadShape;	//main road
	std::vector<sf::ConvexShape> middleLine;	//center dotted line
	std::vector<sf::ConvexShape> littleLines;
	std::vector<sf::ConvexShape> stripedLine;	//red and white stripes
};

