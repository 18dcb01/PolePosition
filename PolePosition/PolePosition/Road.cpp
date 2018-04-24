#include "stdafx.h"
#include "Road.h"
#include <vector>


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
	drawOuterLine(position, speed, carpos);
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
	double mult = 900;
	int width, height;
	double offset;

	//gets the y values

	middleLine.clear();
	for (int i = (carpos / 1500) * 1500; mult / (i-carpos) > 0.03||carpos>i; i+=1500)
	{
		if (i>carpos-750)
		{

			sf::ConvexShape shape;
			shape.setPointCount(4);
			shape.setPoint(0, sf::Vector2f(0, (216.5 + mult / (i + 750 - carpos) * 245)));//top
			if (i > carpos)
				shape.setPoint(2, sf::Vector2f(0, (216.5 + mult / (i - carpos) * 245)));//bottom

			//if its off the screen
			if (shape.getPoint(2).y > 448|| shape.getPoint(2).y <=0)
				shape.setPoint(2, sf::Vector2f(0, 448));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <=0)
				shape.setPoint(0, sf::Vector2f(0, 448));

			
			//other side
			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));
			
			middleLine.push_back(shape);
		}
	}

	//Setting X values
	for (int i = 0; i < middleLine.size(); i++)
	{
		double ypos = middleLine.at(i).getPoint(0).y;
		//top
		middleLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 0.515), ypos));

		ypos = middleLine.at(i).getPoint(2).y;
		//bottom
		middleLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 0.515), ypos));
	}

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i++)
		windowPtr->draw(middleLine.at(i));

	return;
}


void Road::drawOuterLine(double position, double speed, int carpos)
{
	std::vector<sf::ConvexShape> outerLine;
	double mult = 900;



	//gets the y values
	for (int i = (carpos / 1500) * 1500; mult / (i - carpos) > 0.03 || carpos>i; i += 750)
	{
		if (i>carpos - 750)
		{

			sf::ConvexShape shape;
			shape.setPointCount(4);
			//top
			shape.setPoint(0, sf::Vector2f(0, (216.5 + mult / (i + 750 - carpos) * 245)));
			//bottom
			if (i > carpos)
				shape.setPoint(2, sf::Vector2f(0, (216.5 + mult / (i - carpos) * 245)));

			if (shape.getPoint(2).y > 448 || shape.getPoint(2).y <= 0)
				shape.setPoint(2, sf::Vector2f(0, 448));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <= 0)
				shape.setPoint(0, sf::Vector2f(0, 448));



			//other side
			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));


			//alternate red/white
			if (i % 1500 == 0)
				shape.setFillColor(sf::Color::Red);

			outerLine.push_back(shape);
		}
	}

	//Setting X values
	for (int i = 0; i < outerLine.size(); i++)
	{
		double ypos = outerLine.at(i).getPoint(0).y;
		//draws both sides at once, behind the road
		outerLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		outerLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 1.1), ypos));

		ypos = outerLine.at(i).getPoint(2).y;
		//finding the bottom
		outerLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		outerLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 1.1), ypos));
	}

	//Draw outerLine
	for (int i = 0; i < outerLine.size(); i++)
		windowPtr->draw(outerLine.at(i));

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


//uses the road shape to interpolate where a given thing should be
double Road::getXVal(double height, double percentAcross)
{
	int i = 0;
	//find the relevant road shape
	while (roadShape.at(i).getPoint(2).y < height&&i<roadShape.size()-1)
		i++;
	sf::Shape * curShape = &roadShape.at(i);

	//finds how far down the roadshape it should be
	double percentDown = (height - curShape->getPoint(1).y) / (curShape->getPoint(2).y - curShape->getPoint(1).y);

	//considers the bottom for how far across it should be
	double result = percentDown*(percentAcross*curShape->getPoint(2).x + (1 - percentAcross)*curShape->getPoint(3).x);
	//adds in consideration of the top
	result += (1-percentDown)*(percentAcross*curShape->getPoint(1).x + (1 - percentAcross)*curShape->getPoint(0).x);
	return result;
}
