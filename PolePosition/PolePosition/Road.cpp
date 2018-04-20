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
	for (int i = 0; i < 28; i++)
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
	for (int i = 0; i < middleLine.size(); i += 2)
		windowPtr->draw(middleLine.at(i));

	return;
}


void Road::edit(double position, double speed, int carPos)
{
	editRoad(position, speed);
	editCenterLine(position, speed, carPos);
	editOutsideLines(position, speed);
	editThinLines(position, speed);
	 
	return;
}


//need to fix first two points being set on the wrong spot
//implement rotation after turns
void Road::editRoad(double offset, double playerSpeed)
{
	int width, height, curveAdjustment;
	bool adjust = false;	//used to check if there was a curve earlier in the road
	
	//used curves
	double curves[28];	//size should equal roadShape's size
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
		if (roadCurve.at(curves[i]) >= 0)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				editX(&roadShape, i, 3, offset - 8);
				editX(&roadShape, i, 2, offset + roadShape.at(i).getPoint(2).y + 58);
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
			editX(&roadShape, i, 1, width + roadShape.at(i).getPoint(2).y + 50);

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
		

		//Need to shift over the top of straight segments in response to turns
		for (int k = 0; k < i; k++)
		{
			if (curves[i] != 0)
				adjust = true;
			else
				adjust = false;
		}
		if (adjust)
			curveAdjustment = roadShape.at(i - 1).getPoint(0).x - roadShape.at(i - 1).getPoint(3).x;
		else
			curveAdjustment = 0;
	}


	//Move Curve down
	if (roadSpeedTimer.getElapsedTime().asMilliseconds() > 500 - playerSpeed && playerSpeed > 0)
	{
	}


	return;
}


void Road::editCenterLine(double position, double speed, int carPos)
{
	int width, height;
	double offset;

	//setting the offset to midpoint of the bottom of road
	int last = roadShape.size() - 1;
	offset = roadShape.at(last).getPoint(2).x + roadShape.at(last).getPoint(3).x;
	offset = offset / 2;
	//adjusting offset for width of center line
	last = middleLine.size() - 1;
	offset -= (middleLine.at(last).getPoint(2).x - middleLine.at(last).getPoint(3).x) / 2;

	if (middleLine.at(last).getPoint(0).y > windowPtr->getSize().y)
		resetLineHeight(&middleLine);

	//Setting X values
	//turn right
	if (roadCurve.at(0) >= 0)
	{
		//calculating initial width
		height = windowPtr->getSize().y - middleLine.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0)))
			+ offset;

		for (int i = 0; i < middleLine.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				editX(&middleLine, i, 0, width + height / 100);
				editX(&middleLine, i, 1, width + middleLine.at(i).getPoint(1).y / 100 + 2);
			}
			else
			{
				middleLine.at(i).setPoint(1, middleLine.at(i - 1).getPoint(2));
				middleLine.at(i).setPoint(0, middleLine.at(i - 1).getPoint(3));
			}

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - middleLine.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&middleLine, i, 3, width + height / 100);
			editX(&middleLine, i, 2, width + middleLine.at(i).getPoint(2).y / 100 + 2);
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
			if (i == 0)
			{
				editX(&middleLine, i, 0, width + height / 100);
				editX(&middleLine, i, 1, width + middleLine.at(i).getPoint(1).y / 100 + 2);
			}
			else
			{
				middleLine.at(i).setPoint(1, middleLine.at(i - 1).getPoint(2));
				middleLine.at(i).setPoint(0, middleLine.at(i - 1).getPoint(3));
			}

			//changing width and height to deal with point C, D
			height = windowPtr->getSize().y - middleLine.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&middleLine, i, 3, width + height / 100);
			editX(&middleLine, i, 2, width + middleLine.at(i).getPoint(2).y / 100 + 2);
		}
	}


	//animate line using Y values
	int oldY;
	for (int i = 0; i < middleLine.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			oldY = middleLine.at(i).getPoint(j).y;
			editY(&middleLine, i, j, oldY + (speed / 10));	//divide speed by modifier
		}
	}

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i+= 2)
		windowPtr->draw(middleLine.at(i));

	return;
}


void Road::editOutsideLines(double position, double speed)
{

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