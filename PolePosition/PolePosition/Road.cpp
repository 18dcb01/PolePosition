#include "stdafx.h"
#include "Road.h"


Road::Road(sf::RenderWindow *window, std::vector<double> track)
{
<<<<<<< HEAD
	
	 /*
	 TODO: 
		Because of how convex shape works we will split points up into
		quadralaterals and then render all of them.
	 */
	sf::ConvexShape bleach;
	for (int i = 0; i < 10; i++)
		roadShape.push_back(bleach);

	int windowHeight = window->getSize().y / 2;

	//defining Y values for all points

	//setting the height for all points
	for (int i = 0; i < roadShape.size(); i++)
	{
		//setting each shape to have 4 points
		roadShape.at(i).setPointCount(4);

		//setting A and B points (the top two for the shape)
		//if the shape isn't the first shape, than the height of A, B are the same as C, D of the shape before.
		if (i == 0)
		{
			roadShape.at(i).setPoint(0, sf::Vector2f(0, windowHeight));
			roadShape.at(i).setPoint(1, sf::Vector2f(0, windowHeight));
		}
		else
		{
			roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
			roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(3));
		}

		//Setting C and D shapes (the bottom two points)
		roadShape.at(i).setPoint(2, sf::Vector2f(0, 
			roadShape.at(i).getPoint(0).y + (windowHeight / roadShape.size())));
		roadShape.at(i).setPoint(3, sf::Vector2f(0,
			roadShape.at(i).getPoint(0).y + (windowHeight / roadShape.size())));
	}
	
	windowPtr = window;
	roadCurve = track;
=======
	mainShape.setPointCount( 5 * 2);
	int windowHeight = window->getSize().y / 2;

	//defining Y values for all points
	int right = mainShape.getPointCount();
	//Will be upper half of points due to for loop ending after half.
	for (int left = 0; left < mainShape.getPointCount() / 2; left++)
	{
		right--;
		double height = windowHeight + (windowHeight * 1.0 / (((mainShape.getPointCount() - 1) / 2))*left);
		mainShape.setPoint(left, sf::Vector2f(0, height));
		mainShape.setPoint(right, sf::Vector2f(0, height));
	}

	
	windowPtr = window;
	roadCurve.push_back(2);
>>>>>>> 6f9451b4bd48f6540844e02fbc9e2bac91e8c6f4
}


void Road::drawRoad()
{
	int x, width, height;

	//turn right
	if (roadCurve.at(0) > 1)
<<<<<<< HEAD
	{			
		//calculating initial width
		height = roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0)));

		for (int i = 0; i < roadShape.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				roadShape.at(i).setPoint(0, sf::Vector2f(width, roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width, roadShape.at(i).getPoint(0).y));
			}
			else
			{
				roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
				roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(3));
			}
			
			//changing width and height to deal with point C, D
			roadShape.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(roadCurve.at(0)));

			//Setting C and D shapes (the bottom two points)
			roadShape.at(i).setPoint(2, sf::Vector2f(width, roadShape.at(i).getPoint(2).y));
			roadShape.at(i).setPoint(3, sf::Vector2f(width, roadShape.at(i).getPoint(2).y));
			//TODO: print values to test.
			//std::cout << roadShape.at(i).getPoint(0).x, 
=======
	{
 		for (int left = 0; left < mainShape.getPointCount() / 2; left++)
		{
			right--;
			int height = mainShape.getPoint(left).y;

			//calculating left x values
			int width = 0.001 * pow(height, abs(roadCurve.at(0)));
			mainShape.setPoint(left, sf::Vector2f( width, height));
			std::cout << "Point " << left << ": " << width << ", " << height << "\n";

			//calculating right values
			//will need its own equation in the future
			mainShape.setPoint(right, sf::Vector2f(width + 5, height));
			std::cout << "Point " << right << ": " << width + 5 << ", " << height << "\n";
>>>>>>> 6f9451b4bd48f6540844e02fbc9e2bac91e8c6f4
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

<<<<<<< HEAD
	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
	{
		windowPtr->draw(roadShape.at(i));
	}

	return;
=======
	windowPtr->draw(mainShape);
>>>>>>> 6f9451b4bd48f6540844e02fbc9e2bac91e8c6f4
}