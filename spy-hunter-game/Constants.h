#pragma once


#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"


enum class CarSpeed {
	NONE = 0,
	SLOW = 1,
	REGULAR = 2,
	FAST = 3
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
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};