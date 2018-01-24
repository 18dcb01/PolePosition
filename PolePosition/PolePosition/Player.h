#pragma once
#include "Car.h"
#include <vector>
#include <SFML/Audio.hpp>
class Player :
	public Object
{
public:
	Player();
	~Player();

	void tick();
	void drawDashboard();

private:
	std::vector<sf::Sound> sounds;
};