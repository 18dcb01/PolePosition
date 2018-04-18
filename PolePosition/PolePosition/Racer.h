#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Car.h"
#include "Road.h"
#include "Player.h"

/*
	Is always in either right or left lane.

	//TODO: Make racers renderable.
	//      verify code works.
	//       investigate how this program even works.
*/

const int RACER_SPEED = 10;

class Racer : public Car
{
public:
	Racer(sf::RenderWindow*, Road*,Player *,int);
	~Racer();
	void Render(int);
	void tick();
	//This fixes a weird bug, don't change.
	void setRoadRef(Road*);
private:
	Road * roadPtr;
	Player *carPtr;

	//Is off the screen or not.
	bool isOnScreen;

	//Distance from player.
	double xPlayerOffset;
	double yPlayerOffset;
};