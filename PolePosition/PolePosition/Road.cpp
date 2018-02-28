#include "stdafx.h"
#include "Road.h"


Road::Road(sf::RenderWindow *window, std::vector<double> track)
{
	
	 /*
	 TODO: 
		Because of how convex shape works we will split points up into
		quadralaterals and then render all of them.
	 */
	//mainShape.setPointCount( 5 * 2);
	int windowHeight = window->getSize().y / 2;

	//defining Y values for all points

	//Is number of points.
	int right = 5 * 2;
	//Will be upper half of points due to for loop ending after half.
	for (int left = 0; left < right / 2; left++)
	{
		double height = windowHeight + (windowHeight * 1.0 / (((right - 1) / 2))*left);
		//double height = left * 100;
		pointList[left] = sf::Vector2f(0, height);
		pointList[right] = sf::Vector2f(0, height);
		
	}



	
	windowPtr = window;
	roadCurve.push_back(2.1);
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
			right--;
			int height = pointList[left].y;

			//calculating left x values
			int width = 0.001 * pow(height, abs(roadCurve.at(0)));
			pointList[left] = sf::Vector2f( width, height);
			std::cout << "Point " << left << ": " << width << ", " << height << "\n";



			//calculating right values
			//will need its own equation in the future
			width = 0.002 * pow(height, abs(roadCurve.at(0)));
			pointList[right] = sf::Vector2f(width, height);
			std::cout << "Point " << right << ": " << width + 5 << ", " << height << "\n";
			
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

	sf::CircleShape circle(5, 30);
	circle.setOrigin(5, 5);
	for (int j = 0; j < 10; j++)
	{
		mainShape.setPoint(j, pointList[j]);

		circle.setPosition(pointList[j]);
		circle.setFillColor(sf::Color::Red);
		windowPtr->draw(circle);
	}

	//windowPtr->draw(mainShape);
}