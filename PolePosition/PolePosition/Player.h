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
	void initializeDashboard();
	void drawDashboard();
	void updateSound();

private:
	sf::Sound vroom;
	sf::SoundBuffer buffer;
	float soundPitch;
	bool clutchHeld;
	bool clutch;
	std::vector<sf::Text> dashboard;
	sf::Font aClassic;
};