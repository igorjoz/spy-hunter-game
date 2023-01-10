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
	SDL* sdl = new SDL();
	Window* window = new Window(sdl);
	Game* game = new Game(sdl, window);
	Program* program = new Program(sdl, window, game);

	sdl->initializeSDLVariables();

	BMPService::loadImages(sdl);
	
	window->setInitialSettings();

	program->run();

	delete program;

	return 0;
};
