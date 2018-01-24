#pragma once
#include "Player.h"
#include "Racer.h"
#include <vector>
#include "Direction.h"

class Game
{
public:
	Game();
	~Game();
	void play();

private:
	Player p;
	Racer r[7];
	std::vector<Direction> map;
	std::vector<Object> signs;
	int score;
	time_t startTime;
	void race();
	void tick();
	void render();
	void drawMap();
	void drawBackground();
	sf::RenderWindow window;
};