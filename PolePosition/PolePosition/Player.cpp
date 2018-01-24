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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//turn left
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//turn right
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!clutch)
		{
			//Accel faster if slow
		}
		else
		{
			//Accel faster if fast
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//Decelerate
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		if (!clutchHeld)
		{
			//Clutch
		}
		clutchHeld = true;
	}
	else if (clutchHeld)
	{
		clutchHeld = false;
	}
}


void Player::drawDashboard()
{
}