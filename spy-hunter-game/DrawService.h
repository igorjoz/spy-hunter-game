#pragma once


#include "SDL.h"
#include "Window.h"
#include "Game.h"


class DrawService
{
public:
	static void drawGame(SDL* sdl, Game* game);
	static void drawRoadside(SDL* sdl);
	static void drawDividingLines(SDL* sdl);
	static void drawRoad(SDL* sdl);
	static void drawPlayerCar(SDL* sdl, Game* game);
};

