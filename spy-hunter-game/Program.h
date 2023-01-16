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
	void runWhenIsPaused();
	void runWhenGameIsOver();
	void runWhenGameIsBeingSaved();
	void runGame();
	
	void handleKeyEvents();
	void handleKeyDownEvent();
	void handleKeyDownEventWhenPaused();
	void handleKeyDownEventWhenGameIsOver();
	void handleKeyDownEventWhenGameIsBeingSaved();
	void handleKeyUpEvent();
	void handleQuitEvent();
	
	void renderGUI();
	void renderPauseScreen();
	void renderGameOverScreen();
	void renderGameSavingScreen();
	
	void restart();

	void saveGame();
	void saveToResults();

	// get / set
	bool getIsQuit() const;
	
	void setAreMultipleArrowKeysPressed(bool areMultipleArrowKeysPressed);

private:
	SDL* sdl;
	Window* window;
	Game* game;
	
	const Uint8* keyboardState;
	
	bool isQuit;
	bool isGameBeingSaved;
	bool isGameSaved;
	bool areMultipleArrowKeysPressed;
};

