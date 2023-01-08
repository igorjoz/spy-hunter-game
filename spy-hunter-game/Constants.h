#pragma once


#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"


int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

int const PLAYER_CAR_STARTING_X = SCREEN_WIDTH / 2;
int const PLAYER_CAR_STARTING_Y = SCREEN_HEIGHT - 80;


struct Speed {
	const double FAST = 30.0;
	const double SLOW = 0.35;
};


enum class CarSpeed {
	SLOW = 2,
	REGULAR = 5,
	FAST = 10,
};


enum class CarType {
	PLAYER,
	ENEMY
};


//enum class Direction {
//	NONE,
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN
//};