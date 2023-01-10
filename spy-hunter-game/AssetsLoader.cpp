#include "AssetsLoader.h"


#include "SDL.h"


#include<stdio.h>


void AssetsLoader::loadImages(SDL* sdl) {
	AssetsLoader::loadCharset(sdl);
	AssetsLoader::loadPlayerCar(sdl);
}


// load charset BMP file: "cs8x8.bmp"
void AssetsLoader::loadCharset(SDL* sdl) {
	sdl->charset = SDL_LoadBMP("./assets/charset.bmp");

	if (sdl->charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "player_car.bmp"
void AssetsLoader::loadPlayerCar(SDL* sdl) {
	sdl->playerCar = SDL_LoadBMP("./assets/player_car.bmp");

	if (sdl->playerCar == NULL) {
		printf("SDL_LoadBMP(player_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}

