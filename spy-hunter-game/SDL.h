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
	
	void initializeSourceRectangle();
	void initializeDestinationRectangle();
	void initializeCamera();

	void initializeColors();
	int createColor(int red, int green, int blue);

	void renderFrame();

	// get
	int getWhiteColor() const;
	int getBlackColor() const;
	int getRedColor() const;
	int getGreenColor() const;
	int getBlueColor() const;
	
	// SDL variables
	SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	SDL_Surface* screen;
	SDL_Texture* screenTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	SDL_Rect cameraRectangle;
	
	SDL_Surface* charset;

	SDL_Surface* grass;
	SDL_Surface* powerUp;

	SDL_Surface* playerCar;
	SDL_Surface* enemyCar;
	SDL_Surface* neutralCar;

	SDL_Texture* playerCarTexture;
	SDL_Texture* enemyCarTexture;
	SDL_Texture* neutralCarTexture;

private:
	int whiteColor;
	int blackColor;
	int redColor;
	int greenColor;
	int blueColor;
};

