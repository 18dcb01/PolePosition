#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Car.h"
#include "Road.h"
#include "Player.h"

/*
	Is always in either right or left lane.

	//TODO:
	//      verify code works.
	//       investigate how this program even works.
	//       fix position and speed relative to the player.
	//       unspaghetti this whole mess.
*/

//This might be dumb.
const int RACER_SPEED = 10;

class Racer : public Car
{
public:
	Racer(sf::RenderWindow*, Road*,Player *, sf::Vector2f,int);
	~Racer();
	void Render(int);
	void tick();
	//This fixes a weird bug, don't change.
	void setRoadRef(Road*);
private:
	//TODO: subdivide tick() tasks to reduce spaghetti.
	void updateEntityPositions();
	void adjustPosition();

	//Needs access for turn calculation.
	Road * roadPtr;
	//Needs access for distance differances.
	Player *carPtr;

	//Is off the screen or not.
	bool isOnScreen;

	//Distance from player.
	double xPlayerOffset;
	double yPlayerOffset;
};