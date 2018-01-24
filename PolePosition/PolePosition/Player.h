#pragma once
#include "Car.h"
#include <vector>
#include <SFML/Audio.hpp>
class Player :
	public Car
{
public:
	void drawDashboard();
	Player();
	~Player();
	void tick();

private:
	std::vector<sf::Sound> sounds;
	bool clutchHeld;
	bool clutch;
};