#pragma once
#include "Player.h"
#include "Racer.h"
#include <vector>
#include "Direction.h"
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void play();

private:
	Player p;
	Racer r[7];

	//vector that contains all of the the directions that
	//the track is going to turn.
	std::vector<Direction> map;

	std::vector<Object> signs;
	int score;
	time_t startTime;
	void race();
	void tick();
	void render(sf::RenderWindow*);
	void drawMap(sf::RenderWindow*);
	void drawBackground();



};