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
	void qualify();
	void race();
	void openingMenu();
	void flyBanner();

private:
	//Variables for rendering
	sf::RenderWindow *window;
	sf::Sprite backgroundSprite;
	sf::Texture background;

	//
	Player p;
	Racer r[7];

	//road object; contains the map
	Road road;

	std::vector<Object> signs;
	double time;
	short pState;
	int tickCount;
	
	void tick();
	void render();
	void drawBackground();
	void drawPause();
<<<<<<< HEAD
	void loadTrack();
	void loadObjects();
=======
>>>>>>> Game-mechanics
};