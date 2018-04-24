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


void Road::draw(double position, double speed)
{
	drawRoad(position);
	drawCenterLine(position, speed);
	drawOutsideLines(position, speed);
	drawThinLines(position, speed);

	//roadCurve.at(0) += .001;

	return;
}


void Road::drawRoad(double position)
{
	int width, height, offset;

	//offset will be what allows the road to leave the window if the car drives off
	offset = position;

<<<<<<< HEAD
//need to fix first two points being set on the wrong spot
//implement rotation after turns
void Road::editRoad(double offset, double playerSpeed)
{
	int width, height;
	
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
=======
	//turn right
	if (roadCurve.at(0) >= 0)
	{			
		//calculating initial width
		height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;
>>>>>>> fc81bf19fbd077c959e533a6ea64efaafa70a835

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
			width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

			//Setting D and C shapes (the bottom two points)
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1 + 50,
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
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1.5 + 50,
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
<<<<<<< HEAD
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);

		}
		

		//Need to tilt the later segments in response to curves
		for (int k = 0; k < i; k++)
		{
			//derivative is x = 0.001(curves[i-1])(height^curves[i-1]-1)
			int tanSlope = 0.001 * curves[i - 1] * pow(height, curves[i - 1] - 1);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 81229a37d76ac4b009bf655f8cb7923bc00906ce


			//move top two points of shape i over shift amount
		}
	}
=======
>>>>>>> b2b451e6475b28bede0a1c28672ac5e129f06b91


			//move top two points of shape i over shift amount
=======
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1.5,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1.5 + 50,
				roadShape.at(i).getPoint(2).y));
>>>>>>> fc81bf19fbd077c959e533a6ea64efaafa70a835
		}
	}


	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
		windowPtr->draw(roadShape.at(i));

	roadCurve.at(0) -= .0001;
	return;
}


void Road::drawCenterLine(double position, double speed)
{
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

	//Setting X values
	//turn right
	if (roadCurve.at(0) >= 0)
	{
		//calculating initial width
		height = windowPtr->getSize().y - middleLine.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

		for (int i = 0; i < middleLine.size(); i++)
		{
			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{
				middleLine.at(i).setPoint(0, sf::Vector2f(width + height / 100,
					middleLine.at(i).getPoint(0).y));
				middleLine.at(i).setPoint(1, sf::Vector2f(width + middleLine.at(i).getPoint(1).y / 100 + 2,
					middleLine.at(i).getPoint(1).y));
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
			if (i == 0)
			{
				middleLine.at(i).setPoint(0, sf::Vector2f(width + height / 2,
					middleLine.at(i).getPoint(0).y));
				middleLine.at(i).setPoint(1, sf::Vector2f(width + middleLine.at(i).getPoint(1).y / 2 + 2,
					middleLine.at(i).getPoint(1).y));
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
			middleLine.at(i).setPoint(3, sf::Vector2f(width + height / 2,
				middleLine.at(i).getPoint(3).y));
			middleLine.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 2 + 2,
				middleLine.at(i).getPoint(2).y));
		}
	}

	for (int i = 0; i < middleLine.size(); i++)
	{
		for (int j = 0; j < 4; j++)
			middleLine.at(i).setPoint(j, sf::Vector2f(middleLine.at(i).getPoint(j).x, middleLine.at(i).getPoint(j).y + speed));
	}

	//Draw middleLine
	for (int i = 0; i < middleLine.size(); i+= 2)
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