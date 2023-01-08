#include "BMPService.h"


#include "SDL.h"


#include<stdio.h>


void BMPService::loadImages(SDL* sdl) {
	BMPService::loadCharset(sdl);
	BMPService::loadETI(sdl);
	BMPService::loadPlayerCar(sdl);
}


// load charset BMP file: "cs8x8.bmp"
void BMPService::loadCharset(SDL* sdl) {
	sdl->charset = SDL_LoadBMP("./assets/charset.bmp");

	if (sdl->charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load ETI logo BMP file: "eti.bmp"
void BMPService::loadETI(SDL* sdl) {
	sdl->etiBMP = SDL_LoadBMP("./assets/eti.bmp");

	if (sdl->etiBMP == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "player_car.bmp"
void BMPService::loadPlayerCar(SDL* sdl) {
	sdl->playerCar = SDL_LoadBMP("./assets/player_car.bmp");

	if (sdl->playerCar == NULL) {
		printf("SDL_LoadBMP(player_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}

