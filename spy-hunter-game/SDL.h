#pragma once


#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"


class SDL
{
public:
	SDL();
	~SDL();
	void initializeSDL();
	void initializeWindowAndRenderer();
	
//private:
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* etiBMP;
	SDL_Texture* screenTexture;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
};

