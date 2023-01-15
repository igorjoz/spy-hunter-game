#pragma once


#include"SDL.h"


class AssetsLoader
{
public:
	static SDL* sdl;

	static void initialize(SDL* sdl);
	
	static void loadImages();
	static void loadCharset();

	static void loadGrass();

	static void loadPlayerCar();
	static void loadEnemyCar();
	static void loadNeutralCar();
};

