#pragma once
#include <vector>
#include<SFML\Graphics.hpp>
#include "RoadShape.h"

class Road
{
/*
TODO:

Should be the class that defines the quadratic that will represent the
curvature of the road.

 Uses road shapes to map sf objects to the aforementioned lines.

*/


public:
	Road();
	~Road();

private:
	std::vector<RoadShape> roadShapes;
};

