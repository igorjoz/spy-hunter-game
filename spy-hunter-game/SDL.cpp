#include "SDL.h"


void SDL::freeAllocatedMemory(SDL_Surface* charset, SDL_Surface* etiBMP) {
	SDL_FreeSurface(this->screen);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(etiBMP);

	SDL_DestroyTexture(this->screenTexture);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}
