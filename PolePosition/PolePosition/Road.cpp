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
	lastTrackUsed = 0;


	//Creating Road
	//creating a convex shape with four points and color to add to the roadShape
	sf::ConvexShape roadPiece;
	roadPiece.setFillColor(sf::Color(64, 64, 64));
	roadPiece.setPointCount(4);

	//pushing roadPiece into roadShape, number of shapes is adjustable
	for (int i = 0; i < 28; i++)
		roadShape.push_back(roadPiece);

	std::cout << roadShape.size() << std::endl;
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

double Road::getRoadSize()
{
	return roadShape.size();
}

sf::ConvexShape Road::getRelativeBounds(sf::Vector2f position)
{
	for (int i = 0; i < roadShape.size(); i++)
	{
		//For readability.
		double topCurrentIter = roadShape.at(i).getLocalBounds().top;
		double bottomCurrentIter = roadShape.at(i).getLocalBounds().top - 
			roadShape.at(i).getLocalBounds().height;
		if (position.y < topCurrentIter && position.y > bottomCurrentIter)
			return roadShape.at(i);
	}
	throw std::invalid_argument("Location not valid for road.");
}

bool Road::intersects(sf::FloatRect intersect)
{

//	std::cout << roadShape.size() << '\n';
	for (int i = 0; i < roadShape.size(); i++)
	{
		sf::FloatRect tempBound = roadShape.at(i).getGlobalBounds();
		if (intersect.intersects(tempBound))
			return true;
	}



	return false;
}

void Road::edit(double position, double speed, int carPos)
{
	editRoad(position);
	editCenterLine(position, speed, carPos);
	editOutsideLines(position, speed);
	editThinLines(position, speed);

	return;
}


//issue with lastTrack used not transitioning usefully
//
//
void Road::editRoad(double offset)
{
	int width, height;

	//turn right
	if (roadCurve.at(0) >= 0)
	{
		//calculating initial width
		height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
		width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

	}
	
	//keeps track of where we are on the track
	int j = lastTrackUsed;

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
			width = 0.001 * pow(height, abs(roadCurve.at(j))) + offset;


			//setting A and B points (the top two for the shape)
			//if the shape isn't the first shape, than the x-position of A, B are the same as C, D of the shape before.
			if (i == 0)
			{

				roadShape.at(i).setPoint(0, sf::Vector2f(width + height / 1,
					roadShape.at(i).getPoint(0).y));
				roadShape.at(i).setPoint(1, sf::Vector2f(width + roadShape.at(i).getPoint(1).y / 1 + 50,
					roadShape.at(i).getPoint(1).y));

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
			width = 0.001 * pow(height, abs(roadCurve.at(j))) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);

		}
		//turn left
		else if (roadCurve.at(j) < 0)
		{
			//calculating initial width
			height = windowPtr->getSize().y - roadShape.at(0).getPoint(0).y;
			width = -0.001 * pow(height, abs(roadCurve.at(j))) + offset;


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
			width = -0.001 * pow(height, abs(roadCurve.at(j))) + offset;

			//Setting D and C shapes (the bottom two points)
			editX(&roadShape, i, 3, width + height);
			editX(&roadShape, i, 2, width + roadShape.at(i).getPoint(2).y / 1 + 50);

		}

		//increment j
		j++;
	}

	//update lastTrackUsed
	lastTrackUsed = j;
	//draw Road
	for (int i = 0; i < roadShape.size(); i++)
	{
		windowPtr->draw(roadShape.at(i));
		//uncomment to highlight the points in roadShape.
		
		sf::CircleShape highlight = sf::CircleShape(5);
		for (int j = 0; j < roadShape.at(i).getPointCount(); j++)
		{
			highlight.setPosition(roadShape.at(i).getPoint(j).x, roadShape.at(i).getPoint(j).y);
			highlight.setFillColor(sf::Color::Red);
			if (i % 2 == 0)
				highlight.setFillColor(sf::Color::Blue);
			windowPtr->draw(highlight);
		}
		
	}
	roadCurve.at(0) -= .0001;
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
		width = 0.001 * pow(height, abs(roadCurve.at(0))) + offset;

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


//UTILITY FUNCTIONS
void Road::editX(std::vector<sf::ConvexShape> *shapeList, int shape, int point, int newX)
{
	shapeList->at(shape).setPoint(point, sf::Vector2f(newX, shapeList->at(shape).getPoint(point).y));
}


void Road::editY(std::vector<sf::ConvexShape> *shapeList, int shape, int point, int newY)
{
	shapeList->at(shape).setPoint(point, sf::Vector2f(shapeList->at(shape).getPoint(point).x, newY));
}