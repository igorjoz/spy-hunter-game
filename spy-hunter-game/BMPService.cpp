#include "BMPService.h"


#include "SDL.h"


#include<stdio.h>


// load charset BMP file: "cs8x8.bmp"
void BMPService::loadCharset(SDL* sdl) {
	sdl->charset = SDL_LoadBMP("./charset.bmp");

	if (sdl->charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load ETI logo BMP file: "eti.bmp"
void BMPService::loadETI(SDL* sdl) {
	sdl->etiBMP = SDL_LoadBMP("./eti.bmp");

	if (sdl->etiBMP == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}

