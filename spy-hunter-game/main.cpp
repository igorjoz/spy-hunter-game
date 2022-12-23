#define _USE_MATH_DEFINES


#include<math.h>
#include<stdio.h>
#include<string.h>

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

#include "Constants.h"
#include "Surface.h"


void freeMemoryAllocatedBySDL(SDL_Surface* screen, SDL_Surface* charset, SDL_Surface* etiBMP, SDL_Texture* screenTexture, SDL_Window* window, SDL_Renderer* renderer) {
	SDL_FreeSurface(screen);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(etiBMP);

	SDL_DestroyTexture(screenTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


// events handling
void handleEvents(SDL_Event *event, int* quit, int* frames, double* etiBMPSpeed) {
	while(SDL_PollEvent(&(*event))) {
		switch((*event).type) {
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


//void initializeWindowAndRenderer(SDL_Window* window, SDL_Renderer* renderer) {
//	int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer); // fullscreen mode
//	// windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer); // windowed mode
//
//	if (windowAndRendererCreationCode != 0) {
//		SDL_Quit();
//		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
//
//		exit(1);
//	}
//}

		
int main(int argc, char **argv) {
	int time1, time2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiBMPSpeed;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *etiBMP;
	SDL_Texture *screenTexture;
	SDL_Window *window;
	SDL_Renderer *renderer;

	printf("printf output goes here\n");
	printf("printf testing\n");

	initializeSDL();

	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer); // fullscreen mode
	//rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer); // windowed mode

	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		
		return 1;
	};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Spy Hunter");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE); // turn off cursor visibility

	// load BMP image "cs8x8.bmp"
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		freeMemoryAllocatedBySDL(screen, charset, NULL, screenTexture, window, renderer);
		SDL_Quit();
		
		return 1;
	};
	
	SDL_SetColorKey(charset, true, 0x000000);

	etiBMP = SDL_LoadBMP("./eti.bmp");
	if (etiBMP == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		freeMemoryAllocatedBySDL(screen, charset, etiBMP, screenTexture, window, renderer);
		SDL_Quit();
		
		return 1;
	};

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	time1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiBMPSpeed = 1;

	while (!quit) {
		time2 = SDL_GetTicks();
		delta = (time2 - time1) * 0.001; // time in seconds; time2 - time1 is time in milliseconds since the last screen was drawn
		time1 = time2;

		worldTime += delta;
		distance += etiBMPSpeed * delta;

		SDL_FillRect(screen, NULL, black);

		Surface::drawSurface(screen, etiBMP, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);

		fpsTimer += delta;

		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}

		Surface::printProjectAndTimeInformation(text, screen, charset, red, blue, worldTime, fps);

		SDL_UpdateTexture(screenTexture, NULL, screen->pixels, screen->pitch);
		// SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
		SDL_RenderPresent(renderer);

		handleEvents(&event, &quit, &frames, &etiBMPSpeed);
	}

	freeMemoryAllocatedBySDL(screen, charset, etiBMP, screenTexture, window, renderer);
	SDL_Quit();
	
	return 0;
};
