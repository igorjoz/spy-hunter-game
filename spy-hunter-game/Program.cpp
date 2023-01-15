#include "Program.h"


#include "Constants.h"
#include "Surface.h"
#include "SDL.h"
#include "Window.h"


Program::Program(SDL* sdl, Window* window, Game* game) {
	this->sdl = sdl;
	this->window = window;
	this->game = game;

	if (!this or !this->sdl or !this->window or !this->game) {
		printf("Error: Memory allocation failed.\n");

		exit(1);
	}

	this->keyboardState = nullptr;
	
	this->isQuit = false;
	this->areMultipleArrowKeysPressed = false;
}


Program::~Program() {
	delete sdl;
	delete window;
	delete game;
}


void Program::run() {
	while (!isQuit) {
		bool isPaused = game->getIsPaused();
		
		if (isPaused) {
			window->calculateWorldTime(isPaused);

			window->calculateFPS();

			renderPauseScreen();

			handleKeyEvents();
		}
		else {
			window->calculateWorldTime(isPaused);
			
			game->run();

			window->calculateFPS();

			renderGUI();

			handleKeyEvents();
		}
	}
}


void Program::handleKeyEvents() {
	SDL_Event* event = &sdl->event;

	while (SDL_PollEvent(event)) {
		keyboardState = SDL_GetKeyboardState(NULL);

		switch (event->type) {
		case SDL_KEYDOWN: {
			handleKeyDownEvent();

			break;
		}
		case SDL_KEYUP: {
			handleKeyUpEvent();

			break;
		}
		case SDL_QUIT: {
			handleQuitEvent();

			break;
		}
		};
	}

	window->incrementFramesCount();
	window->maintainConstantFPS();
}


void Program::handleKeyDownEvent() {
	bool isPaused = game->getIsPaused();
	
	if (isPaused) {
		handleKeyDownEventWhenPaused();

		return;
	}

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

	if (keyboardState[SDL_SCANCODE_SPACE]) {
		game->getPlayerCar()->setIsShooting(true);
	}

	if (keyboardState[SDL_SCANCODE_P]) {
		game->setIsPaused(true);
	}

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isQuit = true;
	}

	if (keyboardState[SDL_SCANCODE_N]) {
		restart();
	}
}


void Program::handleKeyDownEventWhenPaused() {
	if (keyboardState[SDL_SCANCODE_P]) {
		game->setIsPaused(false);
	}

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isQuit = true;
	}

	if (keyboardState[SDL_SCANCODE_N]) {
		restart();
	}
}


void Program::handleKeyUpEvent() {
	bool hasVerticalMovement = static_cast<bool>(game->getPlayerCar()->getVerticalMovementDirection());
	bool hasHorizontalMovement = static_cast<bool>(game->getPlayerCar()->getHorizontalMovementDirection());

	if (hasVerticalMovement and !keyboardState[SDL_SCANCODE_UP] and !keyboardState[SDL_SCANCODE_DOWN]) {
		game->stopVerticalMovement();
	}

	if (hasHorizontalMovement and !keyboardState[SDL_SCANCODE_LEFT] and !keyboardState[SDL_SCANCODE_RIGHT]) {
		game->stopHorizontalMovement();
	}

	if (!keyboardState[SDL_SCANCODE_SPACE]) {
		game->getPlayerCar()->setIsShooting(false);
	}
}


void Program::handleQuitEvent() {
	isQuit = true;
}


void Program::renderGUI() {
	DrawService::drawGame();

	DrawService::drawGameInformation();

	sdl->renderFrame();
}


void Program::renderPauseScreen() {
	DrawService::drawPauseScreen();

	sdl->renderFrame();
}


void Program::renderGameOverScreen() {
	DrawService::drawGameOverScreen();

	sdl->renderFrame();
}


void Program::restart() {
	game->restart();

	window->resetTime();
}


bool Program::getIsQuit() const {
	return isQuit;
}


void Program::setAreMultipleArrowKeysPressed(bool areMultipleArrowKeysPressed) {
	this->areMultipleArrowKeysPressed = areMultipleArrowKeysPressed;
}