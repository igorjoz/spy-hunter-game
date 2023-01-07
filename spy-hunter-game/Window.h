#pragma once


#include"SDL.h"


class Window
{
public:
	Window(SDL* sdl);
	void setInitialSettings();

private:
	SDL* sdl;
	int time1;
	int time2;
	int frames;
};

