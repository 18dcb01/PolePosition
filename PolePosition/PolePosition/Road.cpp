#include "stdafx.h"
#include "Road.h"


//Empty constructor
Road::Road()
{
}


Road::Road(sf::RenderWindow *window, std::vector<double> track)
{
	//assigning window and storing the race track
	windowPtr = window;
	roadCurve = track;


	//Creating Road
	//creating a convex shape with four points and color to add to the roadShape
	sf::ConvexShape roadPiece;
	roadPiece.setFillColor(sf::Color(64, 64, 64));
	roadPiece.setPointCount(4);

	//pushing roadPiece into roadShape, number of shapes is adjustable
	for (int i = 0; i < 224; i++)
		roadShape.push_back(roadPiece);

	//setting the height for all points
	resetLineHeight(&roadShape);


	//Creating Striped Center Line
	sf::ConvexShape stripe;
	stripe.setPointCount(4);

	for (int i = 0; i < 9; i++)
		middleLine.push_back(stripe);
	
	resetLineHeight(&middleLine);
}


void Road::draw(double position, double speed, double carpos)
{
	drawRoad(position, carpos);
	drawCenterLine(position, speed, carpos);
	drawOutsideLines(position, speed);
	drawThinLines(position, speed);

	//roadCurve.at(0) += .001;

	return;
}


void Road::drawRoad(double position, int carpos)
{
	int width, height, offset;
	carpos = (carpos / 1000) % roadCurve.size();

	//offset will be what allows the road to leave the window if the car drives off
	offset = position;

	//turn right
	if (roadCurve.at(carpos) >= 0)
	{			
		//calculating initial width
		height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;

		for (int i = 0; i < roadShape.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1, 
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1 + 50, 
					roadShape.at(i).getPoint(1).y));
			}
			else
			{
				roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(2));
				roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
			}
			
			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;

			//Setting D and C shapes (the bottom two points)
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1 + 50,
				roadShape.at(i).getPoint(2).y));
		}
	}
	//turn left
	else if (roadCurve.at(carpos) < 0)
	{
		//calculating initial width

		for (int i = 0; i < roadShape.size(); i++)
		{

			height = windowPtr->getSize().y - roadShape.at(i).getPoint(0).y;
			width = -0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.

				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1.5,
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1.5 + 50,
					roadShape.at(i).getPoint(1).y));

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;

			//Setting D and C shapes (the bottom two points)
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1.5,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1.5 + 50,
				roadShape.at(i).getPoint(2).y));
		}
	}


	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
		windowPtr->draw(roadShape.at(i));

	//roadCurve.at(0) -= .0001;
	return;
}


void Road::drawCenterLine(double position, double speed, int carpos)
{
	double mult = 300;
	int width, height;
	double offset;

	//setting the offset to midpoint of the bottom of road
	int last = roadShape.size() - 1;
	offset = roadShape.at(last).getPoint(2).x + roadShape.at(last).getPoint(3).x;
	offset = offset / 2;
	//adjusting offset for width of center line
	last = middleLine.size() - 1;
	offset -= (middleLine.at(last).getPoint(2).x - middleLine.at(last).getPoint(3).x) / 2 ;

	if (middleLine.at(last).getPoint(0).y > windowPtr->getSize().y)
		resetLineHeight(&middleLine);

	middleLine.clear();
	for (int i = (carpos / 500) * 500; mult / (i-carpos) > 0.05||carpos>i; i+=500)
	{
		if (i>carpos-250)
		{

			sf::ConvexShape shape;
			shape.setPointCount(4);
			shape.setPoint(0, sf::Vector2f(0, (216.5 + mult / (i + 250 - carpos) * 245)));
			if (i > carpos)
				shape.setPoint(2, sf::Vector2f(0, (216.5 + mult / (i - carpos) * 245)));
			else
				shape.setPoint(2, sf::Vector2f(0, 448));

			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));
			
			middleLine.push_back(shape);
		}
	}

	//Setting X values
	//turn right
	if (roadCurve.at(0) >= 0)
	{
		//calculating initial width

		for (int i = 0; i < middleLine.size(); i++)
		{
			height = windowPtr->getSize().y - middleLine.at(i).getPoint(0).y;
			width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
				middleLine.at(i).setPoint(0, sf::Vector2f(width + height / 100,
					middleLine.at(i).getPoint(0).y));
				middleLine.at(i).setPoint(1, sf::Vector2f(width + middleLine.at(i).getPoint(1).y / 100 + 2,
					middleLine.at(i).getPoint(1).y));

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - middleLine.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			middleLine.at(i).setPoint(3, sf::Vector2f(width + height / 100,
				middleLine.at(i).getPoint(3).y));
			middleLine.at(i).setPoint(2, sf::Vector2f(width + middleLine.at(i).getPoint(2).y / 100 + 2,
				middleLine.at(i).getPoint(2).y));
		}
	}
	//turn left
	else if (roadCurve.at(0) < 0)
	{
		//calculating initial width
		height = windowPtr->getSize().y - middleLine.at(0).getPoint(0).y;
		width = -0.001 * pow(height, abs(roadCurve.at(0))) + offset;

		for (int i = 0; i < middleLine.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.

				middleLine.at(i).setPoint(0, sf::Vector2f(width + height / 2,
					middleLine.at(i).getPoint(0).y));
				middleLine.at(i).setPoint(1, sf::Vector2f(width + middleLine.at(i).getPoint(1).y / 2 + 2,
					middleLine.at(i).getPoint(1).y));

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - middleLine.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			middleLine.at(i).setPoint(3, sf::Vector2f(width + height / 2,
				middleLine.at(i).getPoint(3).y));
			middleLine.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 2 + 2,
				middleLine.at(i).getPoint(2).y));
		}
	}

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i++)
		windowPtr->draw(middleLine.at(i));

	return;
}


void Road::drawOutsideLines(double position, double speed)
{

}


void Road::drawThinLines(double position, double speed)
{

}


void Road::resetLineHeight(std::vector<sf::ConvexShape> *line)
{
	int windowHeight = windowPtr->getSize().y / 2;

	for (int i = 0; i < line->size(); i++)
	{
		if (i == 0)
		{
			//Points A and B for first shape
			line->at(0).setPoint(0, sf::Vector2f(0, windowHeight));
			line->at(0).setPoint(1, sf::Vector2f(0, windowHeight));
		}
		else
		{
			//Points A and B after first shape
			line->at(i).setPoint(0, line->at(i - 1).getPoint(2));
			line->at(i).setPoint(1, line->at(i - 1).getPoint(3));
		}

		//Points C and D
		line->at(i).setPoint(2, sf::Vector2f(0,
			line->at(i).getPoint(0).y + (windowHeight / line->size())));
		line->at(i).setPoint(3, sf::Vector2f(0,
			line->at(i).getPoint(1).y + (windowHeight / line->size())));
	}
}