#include "Game.h"
#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}


Game::~Game()
{

}


void Game::play()
{
	//Calls race (twice bc two races)
}


void Game::race()
{
	//A loop - continually calls tick
}


void Game::tick()
{
	p.tick();
	for (int i = 0; i < 7; i++)
	{
		r[i].tick();
	}
	//Calls render, updates player and racers
}


void Game::render()
{
	//First, drawBackground
	drawBackground();
	//Then, drawMap
	drawMap();
	//Then signs, racers, and the player
}


void Game::drawMap()
{

}


void Game::drawBackground()
{

}
