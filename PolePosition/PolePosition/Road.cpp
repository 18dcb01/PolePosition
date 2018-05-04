#include "stdafx.h"
#include "Road.h"
#include <fstream>


//Empty constructor
Road::Road()
{
}


Road::Road(sf::RenderWindow *window)
{
	//assigning window and storing the race track
	windowPtr = window;
	loadTrack();
	lastTrackUsed = 0;

	//Creating Road
	//creating a convex shape with four points and color to add to the roadShape
	sf::ConvexShape roadPiece;
	roadPiece.setFillColor(sf::Color(64, 64, 64));
	roadPiece.setPointCount(4);

	//pushing roadPiece into roadShape
	//number of shapes is adjustable; must be multiple of 224 though
	for (int i = 0; i < 56; i++)
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


void Road::draw()
{
	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
		windowPtr->draw(roadShape.at(i));

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i++)
		windowPtr->draw(middleLine.at(i));

	for (int i = 0; i < stripedLine.size(); i++)
		windowPtr->draw(stripedLine.at(i));

	return;
}


void Road::edit(double position, double speed, int carPos)
{
	editRoad(position, speed);
	editCenterLine(position, speed, carPos);
	editOutsideLines(position, speed, carPos);
	editThinLines(position, speed);

	return;
}

double Road::getCurrentRoadCurve()
{
	try {
		return roadCurve.at(lastTrackUsed);
	}
	catch (const std::out_of_range& oor)
	{
		return 0.0;
	}
}


//need to fix first two points being set on the wrong spot
//implement rotation after turns
void Road::editRoad(double offset, double playerSpeed)
{
	double width, height, newAdjustment;
	double curveAdjustment = 0;	//tracks the turns

								//used curves
	double curves[56];	//size should equal roadShape's size
	int j = lastTrackUsed;	//j = 0
	for (int i = 0; i < roadShape.size(); i++)
	{
		j++;
		if (j >= roadCurve.size())
			j = 0;
		curves[i] = roadCurve.at(j);
	}

	for (int i = 0; i < roadShape.size(); i++)
	{
		//turn right
		if (curves[i] >= 0)
		{
			//setting A and B points (the top two for the shape)
			//setting A and B points (the bottom points)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				editX(&roadShape, i, 3, offset - 4);
				editX(&roadShape, i, 2, offset + roadShape.at(i).getPoint(2).y + 54);
			}
			else
			{
				roadShape.at(i).setPoint(3, roadShape.at(i - 1).getPoint(0));
				roadShape.at(i).setPoint(2, roadShape.at(i - 1).getPoint(1));
			}


			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(curves[i])) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 0, width + height);
			//Setting D and C shapes (the top points)
			editX(&roadShape, i, 0, width + height + curveAdjustment);
			editX(&roadShape, i, 1, width + roadShape.at(i).getPoint(2).y + 50 + curveAdjustment);

		}
		//turn left
		else if (curves[i] < 0)
		{
			//calculating initial width
			height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
			width = -0.001 * pow(height, abs(curves[j])) + offset;


			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				editX(&roadShape, i, 0, width + height);
				editX(&roadShape, i, 1, width + roadShape.at(i).getPoint(1).y + 50);
			}
			else
			{
				roadShape.at(i).setPoint(1, roadShape.at(i - 1).getPoint(2));
				roadShape.at(i).setPoint(0, roadShape.at(i - 1).getPoint(3));
			}

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(curves[j])) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);

		}

		/*
		tilting road portions to repect turns
		It wobbles because of offset, try adding -offset to this equation
		*/
		if (curves[i] != 0)
		{
			newAdjustment = (pow(10, 2 / 3) * (pow(abs(width - offset), curves[i] - 1) / curves[i]));

			if (curves[i] < 0)
				curveAdjustment -= newAdjustment;
			else
				curveAdjustment += newAdjustment;
		}
	}


	//Move Curve down
	if (roadSpeedTimer.getElapsedTime().asMilliseconds() > 500 - playerSpeed && playerSpeed > 0)
	{
		lastTrackUsed++;
		if (lastTrackUsed >= roadCurve.size())
			lastTrackUsed = 0;
		roadSpeedTimer.restart();
	}


	return;
}


void Road::editCenterLine(double position, double speed, int carPos)
{
	double mult = 900;

	//gets the y values
	middleLine.clear();
	for (int i = (carPos / 1500) * 1500; mult / (i - carPos) > 0.1 || carPos>i; i += 1500)
		if (i>carPos - 750)
		{
			sf::ConvexShape shape;
			shape.setPointCount(4);
			shape.setPoint(0, sf::Vector2f(0, (199 + mult / (i + 750 - carPos) * 245)));//top
			if (i > carPos)
				shape.setPoint(2, sf::Vector2f(0, (199 + mult / (i - carPos) * 245)));//bottom

																					  //if its off the screen
			if (shape.getPoint(2).y > 448 || shape.getPoint(2).y <= 0)
				shape.setPoint(2, sf::Vector2f(0, 448));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <= 0)
				shape.setPoint(0, sf::Vector2f(0, 448));

			else if (shape.getPoint(0).y <224)
				shape.setPoint(0, sf::Vector2f(0, 224));

			//other side
			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));

			middleLine.push_back(shape);
		}

	//Setting X values
	for (int i = 0; i < middleLine.size(); i++)
	{
		double ypos = middleLine.at(i).getPoint(0).y;//top
		middleLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 0.515), ypos));

		ypos = middleLine.at(i).getPoint(2).y;//bottom
		middleLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 0.515), ypos));
	}
}


void Road::editOutsideLines(double position, double speed, int carPos)
{
	stripedLine.clear();
	double mult = 900;

	//gets the y values
	for (int i = (carPos / 1500) * 1500; mult / (i - carPos) > 0.1 || carPos>i; i += 750)
		if (i>carPos - 750)
		{
			sf::ConvexShape shape;
			shape.setPointCount(4);
			//top
			shape.setPoint(0, sf::Vector2f(0, (199 + mult / (i + 750 - carPos) * 245)));
			//bottom
			if (i > carPos)
				shape.setPoint(2, sf::Vector2f(0, (199 + mult / (i - carPos) * 245)));

			if (shape.getPoint(2).y > 448 || shape.getPoint(2).y <= 0)
				shape.setPoint(2, sf::Vector2f(0, 448));

			else if (shape.getPoint(2).y <224)
				shape.setPoint(2, sf::Vector2f(0, 224));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <= 0)
				shape.setPoint(0, sf::Vector2f(0, 448));

			else if (shape.getPoint(0).y <224)
				shape.setPoint(0, sf::Vector2f(0, 224));


			//other side
			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));


			//alternate red/white
			if (i % 1500 == 0)
				shape.setFillColor(sf::Color::Red);

			stripedLine.push_back(shape);
		}

	//Setting X values
	for (int i = 0; i < stripedLine.size(); i++)
	{
		double ypos = stripedLine.at(i).getPoint(0).y;//draws both sides at once, behind the road
		stripedLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		stripedLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 1.1), ypos));

		ypos = stripedLine.at(i).getPoint(2).y;//finding the bottom
		stripedLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		stripedLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 1.1), ypos));
	}

}


void Road::editThinLines(double position, double speed)
{

}


void Road::resetLineHeight(std::vector<sf::ConvexShape> *line)
{
	int halfWindowHeight = windowPtr->getSize().y / 2;

	for (int i = 0; i < line->size(); i++)
	{
		if (i == 0)
		{
			//Points C and D for first shape;
			//they should be at the bottom of the screen
			line->at(0).setPoint(2, sf::Vector2f(0, halfWindowHeight * 2));
			line->at(0).setPoint(3, sf::Vector2f(0, halfWindowHeight * 2));
		}
		else
		{
			//Points C and D after first shape
			//should equal the top two points on the last shape
			line->at(i).setPoint(2, line->at(i - 1).getPoint(0));
			line->at(i).setPoint(3, line->at(i - 1).getPoint(1));
		}

		//Points A and B
		line->at(i).setPoint(0, sf::Vector2f(0,
			line->at(i).getPoint(2).y - (halfWindowHeight / line->size())));
		line->at(i).setPoint(1, sf::Vector2f(0,
			line->at(i).getPoint(3).y - (halfWindowHeight / line->size())));
	}
}


//UTILITY FUNCTIONS
void Road::editX(std::vector<sf::ConvexShape> *shapeList, int shape, int point, int newX)
{
	shapeList->at(shape).setPoint(point, sf::Vector2f(newX, shapeList->at(shape).getPoint(point).y));
}


void Road::editY(std::vector<sf::ConvexShape> *shapeList, int shape, int point, int newY)
{
	shapeList->at(shape).setPoint(point, sf::Vector2f(shapeList->at(shape).getPoint(point).x, newY));
}


void Road::loadTrack()
{
	std::fstream stream;
	stream.open("Basic Track.txt", std::ios::in);
	std::string str;
	while (getline(stream, str))
	{
		roadCurve.push_back(stod(str));
	}
}



double Road::getXVal(double height, double percentAcross)
{
	int i = 0;
	//find the relevant road shape
	while (roadShape.at(i).getPoint(2).y > height&&i<roadShape.size() - 1)
		i++;
	sf::Shape * curShape = &roadShape.at(i);

	//finds how far down the roadshape it should be
	double percentDown = (height - curShape->getPoint(1).y) / (curShape->getPoint(2).y - curShape->getPoint(1).y);

	//considers the bottom for how far across it should be
	double result = percentDown*(percentAcross*curShape->getPoint(2).x + (1 - percentAcross)*curShape->getPoint(3).x);
	//adds in consideration of the top
	result += (1 - percentDown)*(percentAcross*curShape->getPoint(1).x + (1 - percentAcross)*curShape->getPoint(0).x);
	return result;
}