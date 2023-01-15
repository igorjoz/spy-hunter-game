#include "AssetsLoader.h"


#include "SDL.h"


#include<stdio.h>


SDL* AssetsLoader::sdl = nullptr;


void AssetsLoader::initialize(SDL* sdl) {
	AssetsLoader::sdl = sdl;
}


void AssetsLoader::loadImages() {
	AssetsLoader::loadCharset();

	AssetsLoader::loadGrass();
	AssetsLoader::loadPowerUp();

	AssetsLoader::loadPlayerCar();
	AssetsLoader::loadEnemyCar();
	AssetsLoader::loadNeutralCar();
}


// load charset BMP file: "cs8x8.bmp"
void AssetsLoader::loadCharset() {
	sdl->charset = SDL_LoadBMP("./assets/charset.bmp");

	if (sdl->charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "player_car.bmp"
void AssetsLoader::loadPlayerCar() {
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
void AssetsLoader::loadEnemyCar() {
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
void AssetsLoader::loadNeutralCar() {
	SDL_Surface* neutralCarSurface = SDL_LoadBMP("./assets/neutral_car.bmp");

	sdl->neutralCar = neutralCarSurface;

	sdl->neutralCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->neutralCar);

	if (sdl->neutralCar == NULL) {
		printf("SDL_LoadBMP(neutral_car.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "grass.bmp"
void AssetsLoader::loadGrass() {
	SDL_Surface* grassSurface = SDL_LoadBMP("./assets/grass.bmp");

	sdl->grass = grassSurface;

	//sdl->playerCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->playerCar);

	if (sdl->grass == NULL) {
		printf("SDL_LoadBMP(grass.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}


// load player car BMP file: "power_up.bmp"
void AssetsLoader::loadPowerUp() {
	SDL_Surface* powerUpSurface = SDL_LoadBMP("./assets/power_up.bmp");

	sdl->powerUp = powerUpSurface;

	//sdl->playerCarTexture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->playerCar);

	if (sdl->powerUp == NULL) {
		printf("SDL_LoadBMP(power_up.bmp) error: %s\n", SDL_GetError());
		delete sdl;

		exit(1);
	}
}