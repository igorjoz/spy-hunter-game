#define _USE_MATH_DEFINES


#include<math.h>
#include<stdio.h>
#include<string.h>

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

#include "Constants.h"

#include "SDL.h"
#include "BMPService.h"
#include "Program.h"
#include "Window.h"
#include "Surface.h"
#include "Game.h"


int main(int argc, char* argv[]) {
	int quit = 0;
	
	SDL* sdl = new SDL();
	Window* window = new Window(sdl);
	Game* game = new Game(sdl, window);
	Program* program = new Program(sdl, window, game);

	if (!sdl or !window or !game or !program) {
		printf("Error: Memory allocation failed.\n");
		
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(sdl->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);

	sdl->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->screenTexture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	sdl->initializeColors();

	BMPService::loadCharset(sdl);
	BMPService::loadETI(sdl);
	
	window->setInitialSettings();

	program->run();

	delete program;

	return 0;
};
