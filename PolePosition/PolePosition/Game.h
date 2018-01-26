#pragma once
#include "Player.h"
#include "Racer.h"
#include <vector>
#include "Direction.h"
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow*);
	~Game();
	void play();

private:
	sf::RenderWindow *window;
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

};