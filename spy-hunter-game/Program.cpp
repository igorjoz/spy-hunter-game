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
		
		double etiBMPSpeed = this->game->getEtiBMPSpeed();
		double distance = this->game->getDistance() + (etiBMPSpeed * delta);
		this->game->setDistance(distance);


		
		int black = SDL_MapRGB(this->sdl->screen->format, 0x00, 0x00, 0x00);
		int green = SDL_MapRGB(this->sdl->screen->format, 0x00, 0xFF, 0x00);
		int red = SDL_MapRGB(this->sdl->screen->format, 0xFF, 0x00, 0x00);
		int blue = SDL_MapRGB(this->sdl->screen->format, 0x11, 0x11, 0xCC);



		SDL_FillRect(this->sdl->screen, NULL, black);

		Surface::drawSurface(this->sdl->screen, this->sdl->etiBMP, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);

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
		Surface::printProjectAndTimeInformation(text, sdl->screen, sdl->charset, red, blue, this->window->getWorldTime(), this->window->getFps());

		SDL_UpdateTexture(sdl->screenTexture, NULL, sdl->screen->pixels, sdl->screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(sdl->renderer, sdl->screenTexture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		
		this->handleKeyEvents();
	}
}


double Program::calculateWorldTime() {
	int sdlTicks = SDL_GetTicks();
	this->window->setFrameFinishTime(sdlTicks);

	int frameFinishTime = this->window->getFrameFinishTime();
	int frameStartTime = this->window->getFrameStartTime();

	double delta = (frameFinishTime - frameStartTime) * 0.001; // time in seconds; finishTime - startTime is time in milliseconds since the last screen was drawn
	this->window->setDelta(delta);
	this->window->setFrameStartTime(frameFinishTime);
	this->window->setFrameFinishTime(frameFinishTime);

	double worldTime = this->window->getWorldTime() + delta;
	this->window->setWorldTime(worldTime);

	return worldTime;
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