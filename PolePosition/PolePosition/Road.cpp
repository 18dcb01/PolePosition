#include "stdafx.h"
#include "Road.h"


Road::Road(sf::RenderWindow *window)
{
	roadSide.setPrimitiveType(sf::Points);
	roadSide.resize(5);
	int windowHeight = window->getSize().y / 2;

	//defining Y values for all points
	for (int i = 0; i < roadSide.getVertexCount(); i++)
	{
		roadSide[i] = sf::Vector2f(0, windowHeight + (windowHeight / roadSide.getVertexCount())*i);
	}
}


void Road::drawCurve()
{
	int x;
	double curve;
	//get right curve

	//turn right
	if (curve > 1)
	{
		for (int i = 1; i <= roadSide.getVertexCount(); i++)
		{
			roadSide[i].position.x = 0.01 * pow(roadSide[i].position.y, abs(curve));
		}
	}
	else if (curve < 1)
	{
		//left
	}
	else
	{
		//straight, this is a linear function, probably
	}
}


void Road::drawRoad()
{

}