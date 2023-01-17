#pragma once


#include "Window.h"
#include "SDL.h"


Window::Window(SDL* sdl)
{
	this->sdl = sdl;
	
	this->frameStartTime = SDL_GetTicks();
	this->frameFinishTime = 0;
	this->frames = 0;

	this->scoreFreezeTime = 0;
	this->powerUpTime = 0;
	
	this->delta = 0;
	this->worldTime = 0.0;
	
	this->fpsTimer = 0.0;
	this->fps = 0.0;
}


void Window::setInitialSettings() {
	SDL_SetWindowTitle(this->sdl->window, "Spy Hunter by Igor Jozefowicz (193257)");
	SDL_ShowCursor(SDL_DISABLE); // turn off cursor visibility
	SDL_SetColorKey(this->sdl->charset, true, 0x000000);
}


double Window::calculateWorldTime(bool isPaused) {
	frameFinishTime = SDL_GetTicks();

	double delta = calculateDelta();

	frameStartTime = frameFinishTime;
	
	if (!isPaused) {
		worldTime += delta;
	}

	return worldTime;
}


double Window::calculateDelta() {
	delta = (frameFinishTime - frameStartTime) * 0.001;

	return delta;
}


void Window::calculateFPS() {
	fpsTimer += delta;

	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	}
}


void Window::decreaseScoreFreezeTime() {
	if (scoreFreezeTime > 0) {
		scoreFreezeTime--;
	}
}


void Window::decreasePowerUpTime() {
	if (powerUpTime > 0) {
		powerUpTime--;
	}
}


void Window::maintainConstantFPS() {
	int frameTime = SDL_GetTicks() - frameStartTime;

	if (FRAME_DELAY > frameTime) {
		SDL_Delay(FRAME_DELAY - frameTime);
	}
}


void Window::incrementFramesCount() {
	frames++;
}


void Window::resetTime() {
	worldTime = 0.0;
}


int Window::getFrameStartTime() {
	return this->frameStartTime;
}


int Window::getFrameFinishTime() {
	return this->frameFinishTime;
}


double Window::getDelta() {
	return this->delta;
}


double Window::getWorldTime() {
	return this->worldTime;
}


int Window::getScoreFreezeTime() {
	return this->scoreFreezeTime;
}


int Window::getPowerUpTime() {
	return this->powerUpTime;
}


double Window::getFpsTimer() {
	return this->fpsTimer;
}


double Window::getFps() {
	return this->fps;
}


void Window::setDelta(double delta) {
	this->delta = delta;
}


void Window::setWorldTime(double time) {
	this->worldTime = time;
}


void Window::setScoreFreezeTime(int scoreFreezeTime) {
	this->scoreFreezeTime = scoreFreezeTime;
}


void Window::setPowerUpTime(int powerUpTime) {
	this->powerUpTime = powerUpTime;
}


void Window::setFpsTimer(double fpsTimer) {
	this->fpsTimer = fpsTimer;
}


void Window::setFps(double fps) {
	this->fps = fps;
}