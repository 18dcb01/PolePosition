// PolePosition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <iostream>
#include "Player.h"
#include <time.h>

using namespace std;


int main()
{
	FreeConsole();
	//basic game run
	Game game;
	game.play();
	return 0;
}