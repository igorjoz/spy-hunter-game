#pragma once


#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

int const FRAME_RATE = 144;
int const FRAME_DELAY = 1000 / FRAME_RATE;

int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

int const CAR_WIDTH = 50;
int const CAR_HEIGHT = 90;

int const PLAYER_CAR_STARTING_X = SCREEN_WIDTH / 2;
int const PLAYER_CAR_STARTING_Y = SCREEN_HEIGHT - 80;


//struct Speed {
//	const double FAST = 30.0;
//	const double SLOW = 0.35;
//};


enum class CarSpeed {
	SLOW = 1,
	REGULAR = 2,
	FAST = 3,
};


enum class CarType {
	PLAYER,
	ENEMY
};


enum class MovementDirection {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};