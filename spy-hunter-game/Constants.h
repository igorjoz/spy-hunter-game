#pragma once


#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"


int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

struct Speed {
	const double FAST = 30.0;
	const double SLOW = 0.35;
};

//struct Color {
//	const Uint32 RED = 0xFF0000;
//	const Uint32 GREEN = 0x00FF00;
//	const Uint32 BLUE = 0x0000FF;
//	const Uint32 WHITE = 0xFFFFFF;
//	const Uint32 BLACK = 0x000000;
//};