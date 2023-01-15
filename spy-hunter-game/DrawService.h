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
	static void drawRoadside();
	static void drawRoad();
	static void drawPowerUp();
	static void drawCars();
	
	static void drawDividingLines();
	
	static void drawPlayerCar();
	static void drawEnemyCar();
	static void drawNeutralCar();
	
	static void drawPlayerCarBorder();
	static void drawBullets();

	static void drawGameInformation();
	static void drawListOfImplementedFunctionalities();
	static void drawPauseScreen();
	static void drawGameOverScreen();
};

