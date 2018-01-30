#pragma once
#include "Player.h"
#include "Racer.h"
#include <vector>
#include "Direction.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>

class Game
{
public:
	Game(sf::RenderWindow*);
	~Game();
	void play();

private:
	//Variables for rendering
	sf::RenderWindow *window;
	sf::Sprite background;

	//
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
	void render();
	void drawMap();
	void drawBackground();



};