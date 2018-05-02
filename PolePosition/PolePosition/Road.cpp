#include "stdafx.h"
#include "Road.h"
<<<<<<< HEAD
#include <vector>
=======
#include <fstream>
>>>>>>> Game-mechanics


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

<<<<<<< HEAD
=======
	//new system? would break middle line; ask Daniel before implementing
	//creating pre-loaded convex shapes to piece together to make turns;
	//same scaling same as signs

>>>>>>> Game-mechanics
	//Creating Road
	//creating a convex shape with four points and color to add to the roadShape
	sf::ConvexShape roadPiece;
	roadPiece.setFillColor(sf::Color(64, 64, 64));
	roadPiece.setPointCount(4);

	//pushing roadPiece into roadShape, number of shapes is adjustable
	for (int i = 0; i < 28; i++)
		roadShape.push_back(roadPiece);

	//setting the height for all points
	resetLineHeight(&roadShape);
}


<<<<<<< HEAD
void Road::draw(double position, double speed, double carpos)
{
	calcRoad(position, carpos);
	drawOuterLine(position, speed, carpos);

	for (int i = 0; i < roadShape.size(); i++)
		windowPtr->draw(roadShape.at(i));

	drawCenterLine(position, speed, carpos);
	drawThinLines(position, speed);
=======
void Road::draw()
{
	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
		windowPtr->draw(roadShape.at(i));
>>>>>>> Game-mechanics

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i += 2)
		windowPtr->draw(middleLine.at(i));

	return;
}


<<<<<<< HEAD
void Road::calcRoad(double position, int carpos)
{
	int width, height, offset;
	carpos = (carpos / 1000) % roadCurve.size();
=======
void Road::edit(double position, double speed, int carPos)
{
	editRoad(position, speed);
	editCenterLine(position, speed, carPos);
	editOutsideLines(position, speed);
	editThinLines(position, speed);
>>>>>>> Game-mechanics

	return;
}

<<<<<<< HEAD
	//turn right
	if (roadCurve.at(carpos) >= 0)
	{			
		//calculating initial width
		height = windowPtr->getView().getSize().y - roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;
=======
>>>>>>> Game-mechanics

//issue with lastTrack used not transitioning usefully
void Road::editRoad(double offset, double playerSpeed)
{
	int width, height;
	
	//keeps track of where we are on the track
	int curve[28];
	int j = lastTrackUsed;
	for (int i = 0; i < roadShape.size(); i++)
	{
		j++;
		if (j >= roadShape.size())
			j = 0;
		curve[i] = roadCurve.at(j);
	}
	lastTrackUsed = j;

	for (int i = 0; i < roadShape.size(); i++)
	{
		//check if j is out of bounds
		if (j >= roadCurve.size())
			j = 0;

		//turn right
		if (roadCurve.at(j) >= 0)
		{
			//calculating initial width
			height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
			width = 0.001 * pow(height, abs(curve[i])) + offset;


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
<<<<<<< HEAD
			height = windowPtr->getView().getSize().y - roadShape.at(i).getPoint(2).y;
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
=======
			height = windowPtr->getSize().y - roadShape.at(i).getPoint(2).y;
			width = 0.001 * pow(height, abs(curve[i])) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);
>>>>>>> Game-mechanics

		}
		//turn left
		else if (roadCurve.at(j) < 0)
		{
<<<<<<< HEAD

			height = windowPtr->getView().getSize().y - roadShape.at(i).getPoint(0).y;
			width = -0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.

				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1.5,
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1.5 + 50,
					roadShape.at(i).getPoint(1).y));

			//changing width and height to deal with point C, D
			height = windowPtr->getView().getSize().y - roadShape.at(i).getPoint(2).y;
			width = -0.001 * pow(height, abs(roadCurve.at(carpos))) + offset;
=======
			//calculating initial width
			height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
			width = -0.001 * pow(height, abs(curve[i])) + offset;


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
			width = -0.001 * pow(height, abs(curve[i])) + offset;
>>>>>>> Game-mechanics

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);

		}


<<<<<<< HEAD
	//draw Road

	//roadCurve.at(0) -= .0001;
}


void Road::drawCenterLine(double position, double speed, int carpos)
=======
		//check turns and such
		//need to handle rotations and translations and still make 
		for (int k = 1; k < sizeof(curve) / sizeof(curve[0]); k++)
		{
			if (curve[k] > curve[k - 1])
			{
				roadShape.at(k).setRotation((curve[k] - curve[k - 1]));
			}
		}


		//Move Curve down
		if (roadSpeedTimer.getElapsedTime().asMilliseconds() > 500 - playerSpeed && playerSpeed > 0)
		{
			lastTrackUsed++;
			for (int k = 0; k < roadShape.size() - 2; k++)
				curve[k] = curve[k + 1];
			curve[roadShape.size() - 1] = lastTrackUsed;
		}
	}

	return;
}


void Road::editCenterLine(double position, double speed, int carPos)
>>>>>>> Game-mechanics
{
	double mult = 900;

<<<<<<< HEAD
	//gets the y values
	middleLine.clear();
	for (int i = (carpos / 1500) * 1500; mult / (i-carpos) > 0.1||carpos>i; i+=1500)
		if (i>carpos-750)
		{
			sf::ConvexShape shape;
			shape.setPointCount(4);
			shape.setPoint(0, sf::Vector2f(0, (199 + mult / (i + 750 - carpos) * 245)));//top
			if (i > carpos)
				shape.setPoint(2, sf::Vector2f(0, (199 + mult / (i - carpos) * 245)));//bottom

			//if its off the screen
			if (shape.getPoint(2).y > 448|| shape.getPoint(2).y <=0)
				shape.setPoint(2, sf::Vector2f(0, 448));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <=0)
				shape.setPoint(0, sf::Vector2f(0, 448));
=======
	//setting the offset to midpoint of the bottom of road
	int last = roadShape.size() - 1;
	offset = roadShape.at(last).getPoint(2).x + roadShape.at(last).getPoint(3).x;
	offset = offset / 2;
	//adjusting offset for width of center line
	last = middleLine.size() - 1;
	offset -= (middleLine.at(last).getPoint(2).x - middleLine.at(last).getPoint(3).x) / 2;
>>>>>>> Game-mechanics

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
<<<<<<< HEAD
		double ypos = middleLine.at(i).getPoint(0).y;//top
		middleLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 0.515), ypos));

		ypos = middleLine.at(i).getPoint(2).y;//bottom
		middleLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, 0.485), ypos));
		middleLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 0.515), ypos));
	}
=======
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
>>>>>>> Game-mechanics

	for (int i = 0; i < middleLine.size(); i++)
		windowPtr->draw(middleLine.at(i));//draw everything
}

<<<<<<< HEAD
=======
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
>>>>>>> Game-mechanics

void Road::drawOuterLine(double position, double speed, int carpos)
{
	std::vector<sf::ConvexShape> outerLine;
	double mult = 900;

	//gets the y values
	for (int i = (carpos / 1500) * 1500; mult / (i - carpos) > 0.1 || carpos>i; i += 750)
		if (i>carpos - 750)
		{
<<<<<<< HEAD
			sf::ConvexShape shape;
			shape.setPointCount(4);
			//top
			shape.setPoint(0, sf::Vector2f(0, (199 + mult / (i + 750 - carpos) * 245)));
			//bottom
			if (i > carpos)
				shape.setPoint(2, sf::Vector2f(0, (199 + mult / (i - carpos) * 245)));
=======
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
>>>>>>> Game-mechanics

			if (shape.getPoint(2).y > 448 || shape.getPoint(2).y <= 0)
				shape.setPoint(2, sf::Vector2f(0, 448));

<<<<<<< HEAD
			else if (shape.getPoint(2).y <224)
				shape.setPoint(2, sf::Vector2f(0, 224));

			if (shape.getPoint(0).y > 448 || shape.getPoint(0).y <= 0)
				shape.setPoint(0, sf::Vector2f(0, 448));
=======
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
>>>>>>> Game-mechanics

			else if (shape.getPoint(0).y <224)
				shape.setPoint(0, sf::Vector2f(0, 224));


			//other side
			shape.setPoint(1, shape.getPoint(0));
			shape.setPoint(3, shape.getPoint(2));

<<<<<<< HEAD
=======
void Road::editOutsideLines(double position, double speed)
{
>>>>>>> Game-mechanics

			//alternate red/white
			if (i % 1500 == 0)
				shape.setFillColor(sf::Color::Red);

			outerLine.push_back(shape);
		}

	//Setting X values
	for (int i = 0; i < outerLine.size(); i++)
	{
		double ypos = outerLine.at(i).getPoint(0).y;//draws both sides at once, behind the road
		outerLine.at(i).setPoint(0, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		outerLine.at(i).setPoint(1, sf::Vector2f(getXVal(ypos, 1.1), ypos));

		ypos = outerLine.at(i).getPoint(2).y;//finding the bottom
		outerLine.at(i).setPoint(3, sf::Vector2f(getXVal(ypos, -0.1), ypos));
		outerLine.at(i).setPoint(2, sf::Vector2f(getXVal(ypos, 1.1), ypos));
	}

	//Draw outerLine
	for (int i = 0; i < outerLine.size(); i++)
		windowPtr->draw(outerLine.at(i));
}


void Road::editThinLines(double position, double speed)
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


<<<<<<< HEAD
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
=======
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
>>>>>>> Game-mechanics
