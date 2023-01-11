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
	while (!getIsQuit()) {		
		window->calculateWorldTime();

		game->run();

		window->calculateFPS();

		sdl->printGameInformation(game->getScore(), window->getWorldTime(), window->getFps());

		sdl->renderFrame();
		
		handleKeyEvents();

		window->maintainConstantFPS();
	}
}


void Program::handleKeyEvents() {
	SDL_Event* event = &sdl->event;
	
	while (SDL_PollEvent(event)) {
		Uint32 eventType = event->type;
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

		printf("Key !pressed: %d\n", keyboardState[SDL_SCANCODE_UP]);
		printf("Key #pressed: %d\n", keyboardState[SDL_SCANCODE_LEFT]);

		switch (event->type) {
			case SDL_KEYDOWN: {
				game->handleArrowKeyPressed();

				if (keyboardState[SDL_SCANCODE_UP]) {
					game->handleArrowUpKeyPressed();
				}

				if (keyboardState[SDL_SCANCODE_DOWN]) {
					game->handleArrowDownKeyPressed();
				}

				if (keyboardState[SDL_SCANCODE_LEFT]) {
					game->handleArrowLeftKeyPressed();
				}

				if (keyboardState[SDL_SCANCODE_RIGHT]) {
					game->handleArrowRightKeyPressed();
				}

				if (keyboardState[SDL_SCANCODE_ESCAPE]) {
					setIsQuit(true);
				}

				break;
			}

			case SDL_KEYUP: {
				game->handleKeyUp();

				break;
			}
			case SDL_QUIT: {
				setIsQuit(true);

				break;
			}
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