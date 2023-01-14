#pragma once


#include<stdio.h>
#include<string.h>

#include "Constants.h"


#include "SDL.h"
#include "Window.h"
#include "Game.h"


//extern "C" {
//	#include"./SDL2-2.0.10/include/SDL.h"
//	#include"./SDL2-2.0.10/include/SDL_main.h"
//}


class Surface
{
public:
	static SDL* sdl;
	static Window* window;
	static Game* game;

	static void initialize(SDL* sdl, Window* window, Game* game);
	
	void static printString(int x, int y, const char* text);
	void static drawSurface(SDL_Surface* sprite, int x, int y);
	void static drawPixel(int x, int y, Uint32 color);
	void static drawLine(int x, int y, int l, int dx, int dy, Uint32 color);
	void static drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
};
