#pragma once


#include"SDL.h"
#include"Window.h"
#include"PlayerCar.h"


class Game
{
public:
	Game(SDL* sdl, Window* window);
	~Game();
	void run();
	void drawRoadside();
	void drawRoad();
	void drawPlayerCar();

	void handleArrowKeyPressed();
	void handleArrowUpKeyPressed();
	void handleArrowDownKeyPressed();
	void handleArrowLeftKeyPressed();
	void handleArrowRightKeyPressed();
	void handleKeyUp();
	
	// get / set
	PlayerCar* getPlayerCar();
	int getScore();
	
private:
	SDL* sdl;
	Window* window;
	PlayerCar* playerCar;

	int score;
};

