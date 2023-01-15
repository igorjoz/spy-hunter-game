#define _USE_MATH_DEFINES


#include<math.h>
#include<stdio.h>
#include<string.h>

#include "SDL2-2.0.10/include/SDL.h"
#include "SDL2-2.0.10/include/SDL_main.h"

#include "Constants.h"

#include "SDL.h"
#include "AssetsLoader.h"
#include "Program.h"
#include "Game.h"
#include "Window.h"
#include "Surface.h"


int main(int argc, char* argv[]) {
	SDL* sdl = new SDL();
	Window* window = new Window(sdl);
	Game* game = new Game(sdl, window);
	AssetsLoader::initialize(sdl);
	DrawService::initialize(sdl, window, game);
	Surface::initialize(sdl, window, game);
	Program* program = new Program(sdl, window, game);

	sdl->initializeSDLVariables();
	AssetsLoader::loadImages();
	window->setInitialSettings();

	program->run();

	delete program;

	return 0;
};
