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
	void handleKeyDownEventWhenPaused();
	void handleKeyUpEvent();
	void handleQuitEvent();
	
	void renderGUI();
	void renderPauseScreen();
	void renderGameOverScreen();
	
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
	bool areMultipleArrowKeysPressed;
};

