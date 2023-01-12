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
	this->areMultipleArrowKeysPressed = true;
}


Program::~Program()
{
	delete sdl;
	delete window;
	delete game;
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

		switch (event->type) {
		case SDL_KEYDOWN: {
			if (keyboardState[SDL_SCANCODE_UP] or keyboardState[SDL_SCANCODE_DOWN] or keyboardState[SDL_SCANCODE_LEFT] or keyboardState[SDL_SCANCODE_RIGHT]) {
				game->handleArrowKeyPressed();
			}

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
			bool hasVerticalMovement = static_cast<bool>(game->getPlayerCar()->getVerticalMovementDirection());
			bool hasHorizontalMovement = static_cast<bool>(game->getPlayerCar()->getHorizontalMovementDirection());

			if (hasVerticalMovement and !keyboardState[SDL_SCANCODE_UP] and !keyboardState[SDL_SCANCODE_DOWN]) {
				game->stopVerticalMovement();
			}

			if (hasHorizontalMovement and !keyboardState[SDL_SCANCODE_LEFT] and !keyboardState[SDL_SCANCODE_RIGHT]) {
				game->stopHorizontalMovement();
			}

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


void Program::setAreMultipleArrowKeysPressed(bool areMultipleArrowKeysPressed) {
	this->areMultipleArrowKeysPressed = areMultipleArrowKeysPressed;
}