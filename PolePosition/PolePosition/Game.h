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
	std::vector<Direction> map;
	std::vector<Object> signs;
	int score;
	double time;
	sf::RenderWindow window;
	void race();
	void tick();
	void render();
	void drawMap(sf::RenderWindow*);
	void drawBackground();
	void openingMenu();
	void drawPause();
	short pState;
	int tickCount;
};