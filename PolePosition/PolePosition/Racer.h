#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Car.h"
#include "Road.h"
#include "Player.h"

/*
TODO:
	1. Finish scale.
	2. Handle changing sprites.
	3. Follow the road.
*/

const double RACER_SPEED = 10;

class Racer : public Car
{
public:
	Racer(sf::RenderWindow*, Road*,Player *,int);
	~Racer();
	void render();
	void tick();
	//This fixes a weird bug, don't change.
	void setRoadRef(Road*);
private:
	//Subdivide tick();
	void updateEntitys();
	void handleScaling();

	Road * roadPtr;
	Player *carPtr;

	//Is off the screen or not.
	bool isOnScreen;

	//Distance from player.
	double xPlayerOffset;
	double yPlayerOffset;
	//Actual size for scaling.
	double xRealHeight;
	double yRealHeight;
};