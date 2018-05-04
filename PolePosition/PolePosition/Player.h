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
	void updateSound();
	void playSound();
	void pauseSound();
	void awardPoints(int);
	int getScore();


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
	void initializeSprites();
	int * tickCount;
	int lapStart;
};