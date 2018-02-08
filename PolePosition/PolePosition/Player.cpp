#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <SFML\Audio.hpp>
#include <iostream>

using namespace std;


Player::Player() : Car()
{
	clutchHeld = false;
	buffer.loadFromFile("CarVroom.wav");
	vroom.setBuffer(buffer);
	vroom.setLoop(true);
}


Player::~Player()
{
}


void Player::playSound()
{
	vroom.play();
}


void Player::pauseSound()
{
	vroom.pause();
}


void Player::tick()
{
	//Controls
	//Turn left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		speed[0] -= .25;
	//Turn right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		speed[0] += .25;
	//If overturned, crash
	if (speed[0] <= -14 || speed[0] >= 14)
	{
		//crash
	}
	//Accelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && speed[1] < 300)
	{
		double accel = 0;
		double num = exp(-.04*(speed[1]-150));
		if (!clutch)
		{
			//Accel faster if slow
			accel = .75 - (.75 / (1 + (.25 * num)));
		}
		else
		{
			//Accel faster if fast, with a limit near max speed
			accel = (2 / (1 + num)) * (1.5 - (1.5 / (1 + num)));
		}
		speed[1] += accel;
		updateSound();
	}
	//Decelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed[1] >= 2)
			speed[1] -= 2;
		else if (speed[1] > 0)
			speed[1] = 0;
		updateSound();
	}
	//Clutch
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		if (!clutchHeld)
			clutch = !clutch;
		clutchHeld = true;
	}
	else if (clutchHeld)
		clutchHeld = false;

	//Update pos
	position[0] += speed[0];
	position[1] += speed[1];

	//Draw dashboard
}


void Player::updateSound()
{
	soundPitch = (.4 * (speed[1] / 300)) + .8;
	if (clutch)
		soundPitch -= .1;
	vroom.setPitch(soundPitch);
}


void Player::drawDashboard()
{
}