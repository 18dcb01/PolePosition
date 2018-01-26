#include "stdafx.h"
#include "Player.h"


Player::Player() : Car()
{
	clutchHeld = false;
}


Player::~Player()
{
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
	//Accelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!clutch)
		{
			//Accel faster if slow
			if (speed[1] <= 100)
				speed[1] += .75;
			else
				speed[1] += .25;
		}
		else
		{
			//Accel faster if fast
			if (speed[1] > 100)
				speed[1] += .75;
			else
				speed[1] += .25;
		}
	}
	//Decelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed[1] >= 2)
			speed[1] -= 2;
		else if (speed[1] > 0)
			speed[1] = 0;
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


void Player::drawDashboard()
{
}