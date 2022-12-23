#pragma once


#include<stdio.h>
#include<string.h>

#include "Constants.h"


extern "C" {
	#include"./SDL2-2.0.10/include/SDL.h"
	#include"./SDL2-2.0.10/include/SDL_main.h"
}


class Surface
{
public:
	void static printString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
	void static drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void static drawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void static drawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void static drawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	void static printProjectAndTimeInformation(char* text, SDL_Surface* screen, SDL_Surface* charset, int red, int blue, double worldTime, double fps);
};
