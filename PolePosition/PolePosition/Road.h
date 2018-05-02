#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdexcept>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class Road
{
public:
	Road();
	Road(sf::RenderWindow*);

	//everything in here
	void draw();
	void edit(double, double, int);
	double getXVal(double, double);


	double getCurrentRoadCurve();
private:
	//drawing functions
	void editRoad(double, double);
	void editCenterLine(double, double, int);
	void editOutsideLines(double, double, int);
	void editThinLines(double, double);
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