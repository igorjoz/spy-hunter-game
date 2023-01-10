#include "SDL.h"


#include "Constants.h"


#include<stdio.h>


SDL::SDL() {
	this->initializeSDL();
	this->initializeWindowAndRenderer();
}


SDL::~SDL() {
	SDL_FreeSurface(this->screen);
	SDL_FreeSurface(this->charset);
	//SDL_FreeSurface(this->etiBMP);

	SDL_DestroyTexture(this->screenTexture);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
}


void SDL::initializeSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		delete this;

		exit(1);
	}
}


void SDL::initializeWindowAndRenderer() {
	//int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &this->window, &this->renderer); // fullscreen mode
	int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->window, &this->renderer); // windowed mode

	if (windowAndRendererCreationCode != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		delete this;

		exit(1);
	}
}


void SDL::initializeSDLVariables() {
	this->initializeRendererSettings();
	this->initializeScreen();
	this->initializeScreenTexture();
	this->initializeColors();
}


void SDL::initializeRendererSettings() {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(this->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}


void SDL::initializeScreen() {
	this->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}


void SDL::initializeScreenTexture() {
	this->screenTexture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void SDL::initializeColors() {
	this->whiteColor = this->createColor(0xFF, 0xFF, 0xFF);
	this->blackColor = this->createColor(0x00, 0x00, 0x00);
	this->redColor = this->createColor(0xFF, 0x00, 0x00);
	this->greenColor = this->createColor(0x00, 0xFF, 0x00);
	this->blueColor = this->createColor(0x11, 0x11, 0xCC);
}


int SDL::createColor(int red, int green, int blue) {
	int color = SDL_MapRGB(this->screen->format, red, green, blue);
	return color;
}


// get / set
int SDL::getWhiteColor() {
	return this->whiteColor;
}


int SDL::getBlackColor() {
	return this->blackColor;
}


int SDL::getRedColor() {
	return this->redColor;
}


int SDL::getGreenColor() {
	return this->greenColor;
}


int SDL::getBlueColor() {
	return this->blueColor;
}
