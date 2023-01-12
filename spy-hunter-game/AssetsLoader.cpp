#include "AssetsLoader.h"


#include "SDL.h"


#include<stdio.h>


void AssetsLoader::loadImages(SDL* sdl) {
	AssetsLoader::loadCharset(sdl);
	AssetsLoader::loadPlayerCar(sdl);
	AssetsLoader::loadEnemyCar(sdl);
	AssetsLoader::loadNeutralCar(sdl);
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
	SDL_Surface* playerCarSurface = SDL_LoadBMP("./assets/player_car.bmp");
	
	sdl->playerCar = playerCarSurface;

	sdl->playerCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->playerCar);

	if (sdl->playerCar == NULL) {
		printf("SDL_LoadBMP(player_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "enemy_car.bmp"
void AssetsLoader::loadEnemyCar(SDL* sdl) {
	SDL_Surface* enemyCarSurface = SDL_LoadBMP("./assets/enemy_car.bmp");

	sdl->enemyCar = enemyCarSurface;

	sdl->enemyCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->enemyCar);

	if (sdl->enemyCar == NULL) {
		printf("SDL_LoadBMP(enemy_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "neutral_car.bmp"
void AssetsLoader::loadNeutralCar(SDL* sdl) {
	SDL_Surface* neutralCarSurface = SDL_LoadBMP("./assets/neutral_car.bmp");

	sdl->neutralCar = neutralCarSurface;

	sdl->neutralCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->neutralCar);

	if (sdl->neutralCar == NULL) {
		printf("SDL_LoadBMP(neutral_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}

