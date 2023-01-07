#include "Window.h"
#include "SDL.h"


Window::Window(SDL* sdl)
{
	this->sdl = sdl;
	time1 = 0;
	time2 = 0;
	frames = 0;
}


void Window::setInitialSettings() {
	SDL_SetWindowTitle(this->sdl->window, "Spy Hunter by Igor Jozefowicz");
	SDL_ShowCursor(SDL_DISABLE); // turn off cursor visibility
	SDL_SetColorKey(this->sdl->charset, true, 0x000000);
}
