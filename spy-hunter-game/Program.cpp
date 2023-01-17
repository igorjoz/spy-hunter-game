#include "Program.h"


#include "Constants.h"
#include "Surface.h"
#include "SDL.h"
#include "Window.h"
#include "FileService.h"


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
	this->isGameBeingSaved = false;
	this->isGameSaved = false;
	this->areMultipleArrowKeysPressed = false;

	this->results = nullptr;
}


Program::~Program() {
	delete sdl;
	delete window;
	delete game;
}


void Program::run() {
	while (!isQuit) {
		if (game->getIsPaused()) {
			runWhenIsPaused();
		}
		else if (game->getIsGameOver()) {
			runWhenGameIsOver();
		}
		else if (isGameBeingSaved) {
			runWhenGameIsBeingSaved();
		}
		else {
			runGame();
		}
	}
}


void Program::runWhenIsPaused() {
	bool isPaused = game->getIsPaused();
	
	window->calculateWorldTime(isPaused);

	window->calculateFPS();

	renderPauseScreen();

	handleKeyEvents();
}


void Program::runWhenGameIsOver() {
	if (!isGameSaved) {
		saveToResults();

		isGameSaved = true;
	}

	window->calculateWorldTime();

	window->calculateFPS();

	renderGameOverScreen();

	handleKeyEvents();
}


void Program::runWhenGameIsBeingSaved() {
	window->calculateWorldTime();

	window->calculateFPS();

	renderGameSavingScreen();

	handleKeyEvents();
}


void Program::runGame() {
	window->calculateWorldTime();

	game->run();

	window->calculateFPS();

	renderGUI();

	handleKeyEvents();
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
	bool isGameOver = game->getIsGameOver();
	
	if (isPaused) {
		handleKeyDownEventWhenPaused();

		return;
	}
	else if (isGameOver) {
		handleKeyDownEventWhenGameIsOver();

		return;
	}
	else if (isGameBeingSaved) {
		handleKeyDownEventWhenGameIsBeingSaved();

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

	if (keyboardState[SDL_SCANCODE_S]) {
		isGameBeingSaved = true;
		
		saveGame();
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


void Program::handleKeyDownEventWhenGameIsOver() {
	if (keyboardState[SDL_SCANCODE_R]) {
		game->setIsGameOver(false);
		game->restart();

		restart();
	}

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isQuit = true;
	}
}


void Program::handleKeyDownEventWhenGameIsBeingSaved() {
	if (keyboardState[SDL_SCANCODE_R]) {
		game->setIsGameOver(false);
		game->restart();

		restart();
	}

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isQuit = true;
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
	DrawService::drawGameOverScreen(results);

	sdl->renderFrame();
}


void Program::renderGameSavingScreen() {
	DrawService::drawGameSavingScreen();

	sdl->renderFrame();
}


void Program::restart() {
	game->restart();

	window->resetTime();
}


// TODO: Implement saveGame method - display GameSavingScreen
void Program::saveGame() {
	DrawService::drawGameSavingScreen();
}


void Program::saveToResults() {
	int score = game->getScore();
	
	FileService fileService;
	results = fileService.saveToResults(score);
}


bool Program::getIsQuit() const {
	return isQuit;
}


void Program::setAreMultipleArrowKeysPressed(bool areMultipleArrowKeysPressed) {
	this->areMultipleArrowKeysPressed = areMultipleArrowKeysPressed;
}