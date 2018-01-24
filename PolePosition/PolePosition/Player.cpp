#include "stdafx.h"
#include "Player.h"


Player::Player()
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
		speed[0] -= 1;
	//Turn right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		speed[0] += 1;
	//Accelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!clutch)
		{
			//Accel faster if slow
			if (speed[1] <= 50)
				speed[1] += 2;
			else
				speed[1] += 1;
		}
		else
		{
			//Accel faster if fast
			if (speed[1] > 50)
				speed[1] += 2;
			else
				speed[1] += 1;
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

	//Update position
	position[0] += speed[0];
	position[1] += speed[1];

	//Update score based on speed

	drawDashboard();
}


void Player::drawDashboard()
{
}