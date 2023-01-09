#pragma once


#include"SDL.h"
#include"Window.h"
#include"PlayerCar.h"


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
	PlayerCar* getPlayerCar();
	double getDistance();
	double getEtiBMPSpeed();

	void setDistance(double distance);
	void setEtiBMPSpeed(double etiBMPSpeed);
	
private:
	SDL* sdl;
	Window* window;
	PlayerCar* playerCar;

	double distance;
	double etiBMPSpeed;
};

