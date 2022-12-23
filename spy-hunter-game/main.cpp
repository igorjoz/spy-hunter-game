#define _USE_MATH_DEFINES


#include<math.h>
#include<stdio.h>
#include<string.h>

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

#include "Constants.h"
#include "Surface.h"
#include "SDL.h"
#include "Window.h"


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


void initializeSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());

		exit(1);
	}
}


void initializeWindowAndRenderer(SDL_Window** window, SDL_Renderer** renderer) {
	int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &(*window), &(*renderer)); // fullscreen mode
	// windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer); // windowed mode

	if (windowAndRendererCreationCode != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());

		exit(1);
	}
}


// load charset BMP file: "cs8x8.bmp"
void loadCharsetBMP(SDL_Surface** charset, SDL *sdl) {
	*charset = SDL_LoadBMP("./cs8x8.bmp");

	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		sdl->freeAllocatedMemory(NULL, NULL);
		SDL_Quit();

		exit(1);
	}
}


// load ETI logo BMP file: "eti.bmp"
void loadETIBMP(SDL_Surface** etiBMP, SDL_Surface* charset, SDL *sdl) {
	*etiBMP = SDL_LoadBMP("./eti.bmp");

	if (etiBMP == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		sdl->freeAllocatedMemory(charset, NULL);
		SDL_Quit();

		exit(1);
	}
}

void setInitialWindowSettings(SDL_Surface* charset, SDL_Window* window) {
	SDL_SetWindowTitle(window, "Spy Hunter");
	SDL_ShowCursor(SDL_DISABLE); // turn off cursor visibility
	SDL_SetColorKey(charset, true, 0x000000);
}


int main(int argc, char* argv[]) {
	int time1, time2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiBMPSpeed = 1.0;
	
	SDL* sdl = new SDL();
	SDL_Surface* charset;
	SDL_Surface* etiBMP;


	initializeSDL();
	initializeWindowAndRenderer(&sdl->window, &sdl->renderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(sdl->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);

	

	sdl->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->screenTexture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	loadCharsetBMP(&charset, sdl);
	loadETIBMP(&etiBMP, charset, sdl);
	
	setInitialWindowSettings(charset, sdl->window);

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

		Surface::drawSurface(sdl->screen, etiBMP, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);

		fpsTimer += delta;

		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}

		Surface::printProjectAndTimeInformation(text, sdl->screen, charset, red, blue, worldTime, fps);

		SDL_UpdateTexture(sdl->screenTexture, NULL, sdl->screen->pixels, sdl->screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(sdl->renderer, sdl->screenTexture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);

		handleKeyEvents(&sdl->event, &quit, &frames, &etiBMPSpeed);
	}

	sdl->freeAllocatedMemory(charset, etiBMP);
	SDL_Quit();

	return 0;
};
