#pragma once


#include"SDL.h"
#include"Window.h"


class Game
{
public:
	Game(SDL* sdl, Window* window);
	double calculateDistance(double delta);
	void run();

	void handleArrowUpKeyPressed();
	void handleArrowDownKeyPressed();
	void handleArrowLeftKeyPressed();
	void handleArrowRightKeyPressed();
	
	// get / set
	int getPlayerCarX();
	int getPlayerCarY();

	void setPlayerCarX();
	void setPlayerCarY();


	double getDistance();
	double getEtiBMPSpeed();

	void setDistance(double distance);
	void setEtiBMPSpeed(double etiBMPSpeed);
	
private:
	SDL* sdl;
	Window* window;
	
	int playerCarX;
	int playerCarY;

	double distance;
	double etiBMPSpeed;
};

