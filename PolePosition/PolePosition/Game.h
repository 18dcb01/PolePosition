#pragma once
#include "Player.h"
#include "Racer.h"
#include "Road.h"
#include <vector>
#include <iostream>
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
	sf::Sprite backgroundSprite;
	sf::Texture background;

	//
	Player p;
	//Pretty sure this has to be a vector.
	std::vector<Racer> r;

	//road object; contains the map
	Road road;

	std::vector<Object> signs;
	double time;
	short pState;
	int tickCount;
	void race();
	void tick();
	void render();
	void drawBackground();
	void openingMenu();
	void drawPause();
	void loadTrack();
};