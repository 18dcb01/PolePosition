#include "stdafx.h"
#include "Road.h"


Road::Road(sf::RenderWindow *window, std::vector<double> track)
{
	//assigning window and storing the race track
	windowPtr = window;
	roadCurve = track;

	//creating a convex shape with four points and color to add to the roadShape
	sf::ConvexShape roadPiece;
	roadPiece.setFillColor(sf::Color(64, 64, 64));
	roadPiece.setPointCount(4);
	
	//pushing roadPiece into roadShape, number of shapes is adjustable
	//numbers are 7, 14, 28, 56, 112, 224 (14 is recommended, minimal lag with straight edges only at steep turns
	for (int i = 0; i < 224; i++)
		roadShape.push_back(roadPiece);

	//since the road is only in the bottom half of the screen, windHeight is half the actual height
	int windowHeight = window->getSize().y / 2;

	//setting the height for all points
	for (int i = 0; i < roadShape.size(); i++)
	{
		//setting A and B points (the top two for the shape)
		//if the shape isn't the first shape, than the height of A, B are the same as C, D of the shape before.
		if (i == 0)
		{
			roadShape.at(i).setPoint(0, sf::Vector2f(0, windowHeight));
			roadShape.at(i).setPoint(1, sf::Vector2f(0, windowHeight));
		}
		else
		{
			roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(2));
			roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(3));
		}

		//Setting C and D shapes (the bottom two points)
		roadShape.at(i).setPoint(2, sf::Vector2f(0, 
			roadShape.at(i).getPoint(0).y + (windowHeight / roadShape.size())));
		roadShape.at(i).setPoint(3, sf::Vector2f(0,
			roadShape.at(i).getPoint(1).y + (windowHeight / roadShape.size())));
	}
}


void Road::draw(double position, double speed)
{
	drawRoad(position);
	drawCenterLine(position, speed);
	drawOutsideLines(position, speed);
	drawThinLines(position, speed);

	return;
}


void Road::drawRoad(double position)
{
	int width, height, offset;

	//offset will be what allows the road to leave the window if the car drives off
	offset = position;

	//turn right
	if (roadCurve.at(0) >= 0)
	{			
		//calculating initial width
		height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

		for (int i = 0; i < roadShape.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1.5,
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1.5 + 10,
					roadShape.at(i).getPoint(1).y));
			}
			else
			{
				roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(2));
				roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
			}
			
			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1.5,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1.5 + 10,
				roadShape.at(i).getPoint(2).y));
		}
	}
	//turn left
	else if (roadCurve.at(0) < 0)
	{
		//calculating initial width
		height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
		width = -0.001 * pow(height, abs(roadCurve.at(0))) + offset;

		for (int i = 0; i < roadShape.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1.5,
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1.5 + 10,
					roadShape.at(i).getPoint(1).y));
			}
			else
			{
				roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(2));
				roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
			}

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1.5,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1.5 + 10,
				roadShape.at(i).getPoint(2).y));
		}
	}


	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
	{
		windowPtr->draw(roadShape.at(i));
	}

	roadCurve.at(0) += .0001;
	
	return;
}


void Road::drawCenterLine(double position, double speed)
{

}


void Road::drawOutsideLines(double position, double speed)
{

}


void Road::drawThinLines(double position, double speed)
{

}