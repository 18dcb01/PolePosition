#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Car.h"
#include "Road.h"
#include "Player.h"

/*
TODO:
	1. Handle changing sprites.
	2. Follow the road.
*/

const double RACER_SPEED = 10;

class Racer : public Car
{
public:
<<<<<<< HEAD
	Racer(sf::RenderWindow*, Road*,Player *,int);
=======

	Racer(sf::RenderWindow*, Road*,Player *,int);

	Racer();
	Racer(sf::RenderWindow*, int);
	Racer(int);

>>>>>>> 7b7edef0cd929140cbb4bbbc8fcbfa0d408f1637
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
	double xReal;
	double yReal;
};