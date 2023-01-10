#pragma once


#include "SDL.h"
#include "Window.h"
#include "Game.h"
#include "DrawService.h"


class Program
{
public:
	Program(SDL* sdl, Window* window, Game* game);
	~Program();
	void run();
	void handleKeyEvents();

	// get / set
	bool getIsQuit();
	void setIsQuit(bool isQuit);

private:
	SDL* sdl;
	Window* window;
	Game* game;
	
	bool isQuit;
};

