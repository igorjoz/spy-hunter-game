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
	while (!this->getIsQuit()) {
		this->calculateWorldTime();
		double delta = this->window->getDelta();
		double distance = this->game->calculateDistance(delta);

		SDL_FillRect(this->sdl->screen, NULL, this->sdl->getBlackColor());

		int x = SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3;
		int y = SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3;

		Surface::drawSurface(this->sdl->screen, this->sdl->etiBMP, x, y);

		double fpsTimer = this->window->getFpsTimer() + delta;
		double fps = this->window->getFps();

		if (fpsTimer > 0.5) {
			fps = this->window->getFrames() * 2;
			this->window->setFrames(0);
			fpsTimer -= 0.5;
		}

		this->window->setFpsTimer(fpsTimer);
		this->window->setFps(fps);

		char text[128];
		Surface::printProjectAndTimeInformation(text, sdl->screen, sdl->charset, this->sdl->getRedColor(), this->sdl->getBlueColor(), this->window->getWorldTime(), this->window->getFps());

		SDL_UpdateTexture(sdl->screenTexture, NULL, sdl->screen->pixels, sdl->screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(sdl->renderer, sdl->screenTexture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		
		this->handleKeyEvents();
	}
}


double Program::calculateWorldTime() {
	this->window->setFrameFinishTime(SDL_GetTicks());

	double delta = this->calculateDelta();
	
	this->window->setFrameStartTime(this->window->getFrameFinishTime());

	double worldTime = this->window->getWorldTime() + delta;
	this->window->setWorldTime(worldTime);

	return worldTime;
}


double Program::calculateDelta() {
	int frameFinishTime = this->window->getFrameFinishTime();
	int frameStartTime = this->window->getFrameStartTime();

	// time in seconds; finishTime - startTime is time in milliseconds since the last screen was drawn
	double delta = (frameFinishTime - frameStartTime) * 0.001;
	this->window->setDelta(delta);

	return delta;
}


void Program::handleKeyEvents() {
	SDL_Event* event = &this->sdl->event;

	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_KEYDOWN:
			if (event->key.keysym.sym == SDLK_ESCAPE) {
				this->setIsQuit(1);
			}
			else if (event->key.keysym.sym == SDLK_UP) {
				this->game->setEtiBMPSpeed(Speed().FAST);
			}
			else if ((*event).key.keysym.sym == SDLK_DOWN) {
				this->game->setEtiBMPSpeed(Speed().SLOW);
			}

			break;

		case SDL_KEYUP:
			this->game->setEtiBMPSpeed(1.0);

			break;

		case SDL_QUIT:
			this->setIsQuit(1);

			break;
		};
	}

	int frames = this->window->getFrames() + 1;
	this->window->setFrames(frames);
}


bool Program::getIsQuit() {
	return this->isQuit;
}


void Program::setIsQuit(bool isQuit) {
	this->isQuit = isQuit;
}