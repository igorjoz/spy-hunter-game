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
	void handleKeyDownEvent();
	void handleKeyUpEvent();
	void handleQuitEvent();
	
	void drawGUI();
	void drawPauseScreen();
	//void drawGameOverScreen();
	
	void restart();

	// get / set
	bool getIsQuit() const;
	
	void setAreMultipleArrowKeysPressed(bool areMultipleArrowKeysPressed);

private:
	SDL* sdl;
	Window* window;
	Game* game;
	
	const Uint8* keyboardState;
	
	bool isQuit;
	bool isPaused;
	bool areMultipleArrowKeysPressed;
};

