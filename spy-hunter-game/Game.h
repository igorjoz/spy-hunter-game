#pragma once


#include"SDL.h"
#include"Window.h"


class Game
{
public:
	Game(SDL* sdl, Window* window);
	double calculateDistance(double delta);
	
	// get / set
	double getDistance();
	double getEtiBMPSpeed();

	void setDistance(double distance);
	void setEtiBMPSpeed(double etiBMPSpeed);

	//void handleKeyEvents(SDL_Event* event, int* quit, int* frames, double* etiBMPSpeed);
	//void draw(SDL* sdl, Window* window, int* frames, double* etiBMPSpeed);
	
private:
	SDL* sdl;
	Window* window;
	
	double distance;
	double etiBMPSpeed;
};

