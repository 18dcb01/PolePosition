#pragma once
#include "Car.h"
#include <vector>
#include <SFML/Audio.hpp>
class Player :
	public Car
{
public:
	Player();
	~Player();
	void tick();
	void drawDashboard();
	void updateSound();
	void playSound();
	void pauseSound();

private:
	sf::Sound vroom;
	sf::SoundBuffer buffer;
	float soundPitch;
	bool clutchHeld;
	bool clutch;
};