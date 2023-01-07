#pragma once


#include "Window.h"
#include "SDL.h"


Window::Window(SDL* sdl)
{
	this->sdl = sdl;
	
	this->frameStartTime = SDL_GetTicks();
	this->frameFinishTime = 0;
	this->frames = 0;
	this->worldTime = 0.0;
	this->fpsTimer = 0.0;
	this->fps = 0.0;
}


void Window::setInitialSettings() {
	SDL_SetWindowTitle(this->sdl->window, "Spy Hunter by Igor Jozefowicz");
	SDL_ShowCursor(SDL_DISABLE); // turn off cursor visibility
	SDL_SetColorKey(this->sdl->charset, true, 0x000000);
}


int Window::getFrameStartTime() {
	return this->frameStartTime;
}


int Window::getFrameFinishTime() {
	return this->frameFinishTime;
}


int Window::getFrames() {
	return this->frames;
}


double Window::getDelta() {
	return this->delta;
}


double Window::getWorldTime() {
	return this->worldTime;
}


double Window::getFpsTimer() {
	return this->fpsTimer;
}


double Window::getFps() {
	return this->fps;
}


void Window::setFrameStartTime(int time) {
	this->frameStartTime = time;
}


void Window::setFrameFinishTime(int time) {
	this->frameFinishTime = time;
}


void Window::setFrames(int frames) {
	this->frames = frames;
}


void Window::setDelta(double delta) {
	this->delta = delta;
}


void Window::setWorldTime(double time) {
	this->worldTime = time;
}


void Window::setFpsTimer(double fpsTimer) {
	this->fpsTimer = fpsTimer;
}


void Window::setFps(double fps) {
	this->fps = fps;
}