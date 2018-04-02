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
	for (int i = 0; i < 14; i++)
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

//Only to be called after x coordnates are set.
double Road::getRoadCenterXCoord(double objectHeight)
{
	//get points with similar heights to our car.
	sf::Vector2f *champPtr = &roadShape.at(0).getPoint(0);
	sf::ConvexShape *shapePtr = &roadShape.at(0);

	for (int i = 0; i < roadShape.size(); i++)
	{
		for (int j = 0; j < roadShape.at(i).getPointCount(); j++)
		{
			//if Point's y value is closer to our y value than the current champ.
			//Replace our current champ.
			if (abs(roadShape.at(i).getPoint(j).y - objectHeight) <
				abs(champPtr->y - objectHeight))
			{
				champPtr = &roadShape.at(i).getPoint(j);
				shapePtr = &roadShape.at(i);
			}
				
		}
	}
	
	//iterate through our champ's home shape and find mid x val.
	for (int i = 0; i < shapePtr->getPointCount(); i++)
	{
		if (champPtr->x == shapePtr->getPoint(i).x &&
			champPtr->y != shapePtr->getPoint(i).y)
			return (champPtr->x + shapePtr->getPoint(i).x) / 2;
	}

	std::cout << "Isaac made a mistake!" << std::endl;
	//If function fails, prevent error.
	return windowPtr->getSize().x / 2;
}

bool Road::intersects(sf::FloatRect intersect)
{
	for (int i = 0; i < roadShape.size(); i++)
	{
		sf::FloatRect tempBound = roadShape.at(i).getGlobalBounds();
		if (intersect.intersects(tempBound))
			return true;
	}

	return false;
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
			roadShape.at(i).setPoint(3, sf::Vector2f(width + height / 1.5,
				roadShape.at(i).getPoint(3).y));
			roadShape.at(i).setPoint(2, sf::Vector2f(width + roadShape.at(i).getPoint(2).y / 1.5 + 50,
				roadShape.at(i).getPoint(2).y));
		}
	}


	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
	{
		windowPtr->draw(roadShape.at(i));
		//uncomment to highlight the points in roadShape.
		/*
		sf::CircleShape highlight = sf::CircleShape(5);
		for (int j = 0; j < roadShape.at(i).getPointCount(); j++)
		{
			highlight.setPosition(roadShape.at(i).getPoint(j).x, roadShape.at(i).getPoint(j).y);
			highlight.setFillColor(sf::Color::Red);
			if (i % 2 == 0)
				highlight.setFillColor(sf::Color::Blue);
			windowPtr->draw(highlight);
		}
		*/
	}
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