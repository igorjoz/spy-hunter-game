#pragma once


#include"SDL.h"


class AssetsLoader
{
public:
	static void loadImages(SDL* sdl);
	static void loadCharset(SDL* sdl);
	static void loadPlayerCar(SDL* sdl);
	static void loadEnemyCar(SDL* sdl);
	static void loadNeutralCar(SDL* sdl);
};

