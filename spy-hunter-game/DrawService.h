#pragma once


#include "SDL.h"
#include "Window.h"
#include "Game.h"


class DrawService
{
public:
	static SDL* sdl;
	static Window* window;
	static Game* game;
	
	static void initialize(SDL* sdl, Window* window, Game* game);
	
	static void drawGame();
	static void drawCars();
	static void drawRoadside();
	static void drawDividingLines();
	static void drawRoad();
	static void drawPlayerCar();
	static void drawPlayerCarBorder();
	static void drawEnemyCar();
	static void drawNeutralCar();

	static void drawGameInformation();
	static void drawListOfImplementedFunctionalities();
	static void drawPauseScreen();
};

