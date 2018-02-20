#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

using namespace std;


Player::Player() : Car()
{
}


Player::Player(sf::RenderWindow* w) : Car(w)
{
	clutchHeld = false;
	//Load engine noise
	buffer.loadFromFile("CarVroom.wav");
	vroom.setBuffer(buffer);
	vroom.setLoop(true);
	vroom.play();
	//Declare dashboard text
	sf::Text tTop, tScore, tTime, tLap, tSpeed,
		topScore, score, time, lap, speed;
	dashboard = {tTop, tScore, tTime, tLap, tSpeed,
		topScore, score, time, lap, speed};
	//Initialize font
	if (!aClassic.loadFromFile("Arcade Classic.ttf"))
		cout << "Failed to load font" << endl;
	//Initialize dashboard text
	initializeDashboard();
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
}


//Updates pitch of engine noise based on player's speed
void Player::updateSound()
{
	soundPitch = (.4 * (speed[1] / 300)) + .8;
	if (clutch)
		soundPitch -= .1;
	vroom.setPitch(soundPitch);
}


//Initializes Text objects to be used in dashboard
void Player::initializeDashboard()
{
	for (int i = 0; i < 10; i++)
	{
		dashboard.at(i).setFont(aClassic);
		dashboard.at(i).setCharacterSize(16);
	}
	dashboard.at(0).setString("TOP");
	dashboard.at(0).setPosition(48, 16);
	dashboard.at(0).setFillColor(sf::Color(255, 151, 173));
	dashboard.at(1).setString("SCORE");
	dashboard.at(1).setPosition(16, 48);
	dashboard.at(2).setString("TIME");
	dashboard.at(2).setPosition(224, 16);
	dashboard.at(2).setFillColor(sf::Color(255, 250, 103));
	dashboard.at(3).setString("LAP");
	dashboard.at(3).setPosition(352, 16);
	dashboard.at(3).setFillColor(sf::Color(141, 238, 105));
	dashboard.at(4).setString("SPEED");
	dashboard.at(4).setPosition(320, 48);
	dashboard.at(5).setPosition(192, 16);
	dashboard.at(5).setFillColor(sf::Color(255, 151, 173));
	dashboard.at(6).setPosition(192, 48);
	dashboard.at(7).setPosition(272, 48);
	dashboard.at(7).setFillColor(sf::Color(255, 250, 103));
	dashboard.at(8).setPosition(496, 16);
	dashboard.at(8).setFillColor(sf::Color(141, 238, 105));
	dashboard.at(9).setPosition(464, 48);
}


//Updates the values displayed in the dashboard, then draws the dashboard
void Player::drawDashboard()
{
	//Set the strings for the second half
	/*
	.at(5) is top score
	.at(6) is current score
	.at(7) is time
	.at(8) is lap time
	.at(9) is speed (not turning, just forward speed)
	*/
	dashboard.at(5).setString("99999");
	dashboard.at(6).setString("99999");
	dashboard.at(7).setString("999");
	dashboard.at(8).setString("99\"99");
	int ySpeed = speed[1];
	dashboard.at(9).setString(to_string(ySpeed));
	for (int i = 5; i < 10; i++)
	{
		dashboard.at(i).setOrigin(dashboard.at(i).getLocalBounds().width, 0);
	}
	for (int i = 0; i < 10; i++)
		window->draw(dashboard.at(i));
}