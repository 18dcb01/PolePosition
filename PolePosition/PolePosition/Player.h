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
	Player(sf::RenderWindow*);
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
	std::vector<sf::Text> dashboard;
	sf::Font aClassic;
	void initializeDashboard();
};