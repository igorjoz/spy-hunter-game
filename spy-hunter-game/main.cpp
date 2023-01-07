#define _USE_MATH_DEFINES


#include<math.h>
#include<stdio.h>
#include<string.h>

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

#include "Constants.h"

#include "SDL.h"
#include "BMPService.h"
#include "Program.h"
#include "Window.h"
#include "Surface.h"
#include "Game.h"


void handleKeyEvents(SDL_Event* event, int* quit, int* frames, double* etiBMPSpeed) {
	while (SDL_PollEvent(&(*event))) {
		switch ((*event).type) {
			case SDL_KEYDOWN:
				if ((*event).key.keysym.sym == SDLK_ESCAPE) {
					*quit = 1;
				}
				else if ((*event).key.keysym.sym == SDLK_UP) {
					*etiBMPSpeed = 30.0;
				}
				else if ((*event).key.keysym.sym == SDLK_DOWN) {
					*etiBMPSpeed = 0.35;
				}

				break;

			case SDL_KEYUP:
				*etiBMPSpeed = 1.0;

				break;

			case SDL_QUIT:
				*quit = 1;

				break;
		};
	}

	frames++;
}


int main(int argc, char* argv[]) {
	int time1, time2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiBMPSpeed = 1.0;
	
	SDL* sdl = new SDL();
	Window* window = new Window(sdl);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(sdl->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);

	sdl->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->screenTexture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	BMPService::loadCharset(sdl);
	BMPService::loadETI(sdl);
	
	window->setInitialSettings();

	char text[128];
	int black = SDL_MapRGB(sdl->screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(sdl->screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(sdl->screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(sdl->screen->format, 0x11, 0x11, 0xCC);

	time1 = SDL_GetTicks();

	while (!quit) {
		time2 = SDL_GetTicks();
		delta = (time2 - time1) * 0.001; // time in seconds; time2 - time1 is time in milliseconds since the last screen was drawn
		time1 = time2;

		worldTime += delta;
		distance += etiBMPSpeed * delta;

		SDL_FillRect(sdl->screen, NULL, black);

		Surface::drawSurface(sdl->screen, sdl->etiBMP, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);

		fpsTimer += delta;

		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}

		Surface::printProjectAndTimeInformation(text, sdl->screen, sdl->charset, red, blue, worldTime, fps);

		SDL_UpdateTexture(sdl->screenTexture, NULL, sdl->screen->pixels, sdl->screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(sdl->renderer, sdl->screenTexture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);

		handleKeyEvents(&sdl->event, &quit, &frames, &etiBMPSpeed);
	}

	delete sdl;

	return 0;
};
