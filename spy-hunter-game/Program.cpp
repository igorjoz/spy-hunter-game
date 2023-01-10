#include "Program.h"


#include "Constants.h"
#include "Surface.h"
#include "SDL.h"
#include "Window.h"


Program::Program(SDL* sdl, Window* window, Game* game)
{
	this->sdl = sdl;
	this->window = window;
	this->game = game;

	if (!this or !this->sdl or !this->window or !this->game) {
		printf("Error: Memory allocation failed.\n");

		exit(1);
	}

	this->isQuit = false;
}


Program::~Program()
{
	delete this->sdl;
	delete this->window;
	delete this->game;
}


void Program::run() {
	Uint32 frameStart;
	int frameTime;
	
	while (!getIsQuit()) {		
		frameStart = SDL_GetTicks();

		window->calculateWorldTime();

		game->run();

		window->calculateFPS();

		sdl->printGameInformation(game->getScore(), window->getWorldTime(), window->getFps());

		sdl->renderFrame();
		
		handleKeyEvents();

		frameTime = SDL_GetTicks() - frameStart;
		
		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
}


void Program::handleKeyEvents() {
	SDL_Event* event = &sdl->event;

	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_KEYDOWN:
			game->handleArrowKeyPressed();

			if (event->key.keysym.sym == SDLK_ESCAPE) {
				setIsQuit(1);
			}
			else if (event->key.keysym.sym == SDLK_UP) {
				game->handleArrowUpKeyPressed();
			}
			else if (event->key.keysym.sym == SDLK_DOWN) {
				game->handleArrowDownKeyPressed();
			}
			else if (event->key.keysym.sym == SDLK_LEFT) {
				game->handleArrowLeftKeyPressed();
			}
			else if (event->key.keysym.sym == SDLK_RIGHT) {
				game->handleArrowRightKeyPressed();
			}

			break;

		case SDL_KEYUP:
			game->handleKeyUp();

			break;

		case SDL_QUIT:
			setIsQuit(1);

			break;
		};
	}

	int frames = window->getFrames() + 1;
	window->setFrames(frames);
}


bool Program::getIsQuit() {
	return isQuit;
}


void Program::setIsQuit(bool isQuit) {
	this->isQuit = isQuit;
}