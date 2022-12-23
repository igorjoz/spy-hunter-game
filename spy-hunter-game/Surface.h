#pragma once


extern "C" {
	#include"./SDL2-2.0.10/include/SDL.h"
	#include"./SDL2-2.0.10/include/SDL_main.h"
}


class Surface
{
public:
	void static DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
	void static DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void static DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void static DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void static DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
};
