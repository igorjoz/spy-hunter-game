#include "SDL.h"


#include<stdio.h>


SDL::SDL() {
	this->initializeSDL();
	this->initializeWindowAndRenderer();
}


SDL::~SDL() {
	SDL_FreeSurface(this->screen);
	SDL_FreeSurface(this->charset);
	SDL_FreeSurface(this->etiBMP);

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
	int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &this->window, &this->renderer); // fullscreen mode
	//int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &(*window), &(*renderer)); // fullscreen mode
	// windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer); // windowed mode

	if (windowAndRendererCreationCode != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		delete this;

		exit(1);
	}
}
