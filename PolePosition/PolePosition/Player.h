#pragma once
#include "Car.h"
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Player :
	public Car
{
public:
	Player();
	Player(sf::RenderWindow*, int*, int);
	~Player();
	void tick();
	void drawDashboard(bool);
	void drawClutch();
	void updateSound();
	void playSound();
	void pauseSound();
	void awardPoints(int);
	int getScore();
	void decrementRaceTime();
	void setRaceTime(int);
	void addRaceTime(int);
	int getRaceTime();

private:
	sf::Sound vroom;
	sf::SoundBuffer buffer;
	float soundPitch;
	bool clutchHeld;
	bool clutch;
	std::vector<sf::Text> dashboard;
	sf::Font aClassic;
	int score;
	int highScore;
	void initializeDashboard();
	int * tickCount;
	int lapStart;
	int raceTime;
	double lapTime;
};