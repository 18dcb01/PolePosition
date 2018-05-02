#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>

using namespace std;


Player::Player() : Car()
{
}


Player::Player(sf::RenderWindow* w, int * tickCount_, int color) : Car(w, color)
{
	raceTime = 120;
	//Initialize score and high score
	score = 0;
	fstream scoreFile;
	scoreFile.open("highScore.txt");
	if (scoreFile.is_open())
		scoreFile >> highScore;
	else
	{
		cout << "High score file could not be opened" << endl;
		highScore = 0;
	}
	scoreFile.close();
	//Load engine noise
	tickCount = tickCount_;

	clutchHeld = false;
	buffer.loadFromFile("CarVroom.wav");
	vroom.setBuffer(buffer);
	vroom.setLoop(true);
	//Initialize dashboard text
	if (!aClassic.loadFromFile("Arcade Classic.ttf"))
	{
		cout << "Didn't work dude" << endl;
	}
	sf::Text tTop, tScore, tTime, tLap, tSpeed,
		topScore, score, time, lap, speed;
	dashboard = {tTop, tScore, tTime, tLap, tSpeed,
		topScore, score, time, lap, speed};
	initializeDashboard();

	position[1] = -500;
}


Player::~Player()
{
	std::fstream scoreFile;
	scoreFile.open("highScore.txt",ios::out);
	scoreFile << ((highScore / 10) * 10);
	scoreFile.close();
}


void Player::playSound()
{
	//if not playing, play
	if (vroom.getStatus() != 2)
		vroom.play();
}


void Player::pauseSound()
{
	//if not paused, pause
	if (vroom.getStatus() != 1)
		vroom.pause();
}


//To increase score as the player travels
void Player::awardPoints(int p)
{
	score += p;
	if (score > highScore)
		highScore = score;
}


int Player::getScore()
{
	return score;
}


void Player::tick()
{
	int temp = (*tickCount - lapStart) / 25;
	lapTime = temp + (((*tickCount - lapStart) % 25) * 4 / 100);
	//Controls
	//Turn left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		speed[0] -= .25;
	//Turn right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		speed[0] += .25;
	if (speed[0] > 9 || speed[0] < -9)
		isCrashing = true;
	if (isCrashing)
	{
		speed[1] -= 15;
		if (speed[1] < 0)
			speed[1] = 0;
	}
	//Accelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && speed[1] < 225)
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
	}
	//Decelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speed[1] -= 2;
		if (speed[1] < 0)
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
	if (position[1] < 0)
		lapStart = *tickCount;

	//Update pos
	position[0] += speed[0];
	position[1] += speed[1];
	updateSound();
<<<<<<< HEAD

	score = position[1]+500;
=======
	
	spinny += 80 * speed[1];
	awardPoints(0.05 * speed[1]);
>>>>>>> Game-mechanics
}


//Updates pitch of engine noise based on player's speed
void Player::updateSound()
{
	soundPitch = (.4 * (speed[1] / 300)) + .8;
	//sound is lower when in high gear
	if (clutch)
		soundPitch -= .1;
	vroom.setPitch(soundPitch);
}


void Player::decrementRaceTime()
{
	if (raceTime > 0)
		raceTime--;
}


void Player::setRaceTime(int t)
{
	if (t > 0)
		raceTime = t;
}


void Player::addRaceTime(int t)
{
	if (t > 0)
		raceTime += t;
}


void Player::drawDashboard(bool paused)
{
	//Set the strings for the second half
	int displayHigh = (highScore / 10) * 10;
	dashboard.at(5).setString(to_string(displayHigh));
	int displayScore = (score / 10) * 10;
	dashboard.at(6).setString(to_string(displayScore));
	dashboard.at(7).setString(to_string(raceTime));
	int lapSeconds = (*tickCount - lapStart) / 25;
	int lapCentiseconds = ((*tickCount - lapStart) % 25) * 4;
	if (lapCentiseconds != 0 && !paused)
		lapCentiseconds += rand() % 4;
	dashboard.at(8).setString(
		(lapSeconds < 10 ? "0" : "") + to_string(lapSeconds) + 
		(lapCentiseconds < 10 ? "\"0" : "\"") + to_string(lapCentiseconds));//lap value
	
	int ySpeed = speed[1];
	dashboard.at(9).setString(to_string(ySpeed));//speed value
	for (int i = 5; i < 10; i++)
	{
		dashboard.at(i).setOrigin(dashboard.at(i).getLocalBounds().width, 0);
	}
	for (int i = 0; i < 10; i++)
		window->draw(dashboard.at(i));
}


/*
Creates:
  TOP #####  TIME   LAP ##"##
SCORE #####  ###  SPEED ###
should add mph/km
*/
void Player::initializeDashboard()
{
	for (int i = 0; i < 10; i++)
	{
		dashboard.at(i).setFont(aClassic);
		dashboard.at(i).setCharacterSize(16);
	}
	dashboard.at(0).setString("TOP");
	dashboard.at(0).setPosition(48, 16);
	dashboard.at(0).setFillColor(sf::Color(255, 151, 173));//pink

	dashboard.at(1).setString("SCORE");
	dashboard.at(1).setPosition(16, 48);//white

	dashboard.at(2).setString("TIME");
	dashboard.at(2).setPosition(224, 16);
	dashboard.at(2).setFillColor(sf::Color(255, 250, 103));//yellow

	dashboard.at(3).setString("LAP");
	dashboard.at(3).setPosition(352, 16);
	dashboard.at(3).setFillColor(sf::Color(141, 238, 105));//green

	dashboard.at(4).setString("SPEED");
	dashboard.at(4).setPosition(320, 48);//white

	dashboard.at(5).setPosition(192, 16);//top score value
	dashboard.at(5).setFillColor(sf::Color(255, 151, 173));//pink

	dashboard.at(6).setPosition(192, 48);//score value, white

	dashboard.at(7).setPosition(272, 48);//time value
	dashboard.at(7).setFillColor(sf::Color(255, 250, 103));//yellow

	dashboard.at(8).setPosition(496, 16);//lap value
	dashboard.at(8).setFillColor(sf::Color(141, 238, 105));//green

	dashboard.at(9).setPosition(464, 48);//speed value, white
}