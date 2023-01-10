#pragma once


#include"Window.h"


class Map
{
public:
	static int const ROAD_WIDTH = 250;
	static int const ROAD_HEIGHT = Window::WINDOW_HEIGHT;

	static int const ROAD_LEFT_X = Window::WINDOW_WIDTH / 2 - ROAD_WIDTH / 2;
	static int const ROAD_TOP_Y = 0;

	static int const ROAD_RIGHT_X = ROAD_LEFT_X + ROAD_WIDTH;
	static int const ROAD_BOTTOM_Y = ROAD_TOP_Y + ROAD_HEIGHT;

	static bool checkIfInsideRoad(int x, int y);
	
private:
};

