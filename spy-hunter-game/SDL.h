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
	void initializeSDLVariables();
	void initializeRendererSettings();
	void initializeScreen();
	void initializeScreenTexture();
	void initializeColors();
	int createColor(int red, int green, int blue);

	// get / set
	int getWhiteColor();
	int getBlackColor();
	int getRedColor();
	int getGreenColor();
	int getBlueColor();
	
	// SDL variables
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Texture* screenTexture;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	SDL_Surface* charset;
	SDL_Surface* etiBMP;
	SDL_Surface* playerCar;

private:
	int whiteColor;
	int blackColor;
	int redColor;
	int greenColor;
	int blueColor;
};

