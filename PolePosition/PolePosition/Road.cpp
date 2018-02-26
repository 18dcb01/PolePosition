#include "stdafx.h"
#include "Road.h"


Road::Road(sf::RenderWindow *window, std::vector<double> track)
{
	mainShape.setPointCount( 5 * 2);
	int windowHeight = window->getSize().y / 2;

	//defining Y values for all points
	int right = mainShape.getPointCount();
	//Will be upper half of points due to for loop ending after half.
	for (int left = 0; left < mainShape.getPointCount() / 2; left++)
	{
		right--;
		int height = windowHeight + (windowHeight / mainShape.getPointCount())*left;
		mainShape.setPoint(left, sf::Vector2f(0, height));
		mainShape.setPoint(right, sf::Vector2f(0, height));
	}
	
	windowPtr = window;
	roadCurve.push_back(2);
}


void Road::drawRoad()
{
	int x;
	int right = mainShape.getPointCount();
	//turn right
	if (roadCurve.at(0) > 1)
	{
		
		for (int left = 0; left < mainShape.getPointCount() / 2; left++)
		{
			int height = mainShape.getPoint(left).y;

			//calculating left x values
			int width = 0.01 * pow(height, abs(roadCurve.at(0)));
			mainShape.setPoint(left, sf::Vector2f( width, height));

			//calculating right values
			//will need its own equation in the future
			mainShape.setPoint(right, sf::Vector2f(width + 50, height));
		}
	}
	//turn left
	else if (roadCurve.at(0) < 1)
	{
		//left
	}
	//going straight
	else
	{
		//straight, this is a linear function, probably
	}

	windowPtr->draw(mainShape);
}