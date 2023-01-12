#pragma once


#include"Window.h"


class Map
{
public:
	static int const ROAD_WIDTH = 250;
	static int const ROAD_HEIGHT = Window::WINDOW_HEIGHT;

	static int constexpr ROAD_LEFT_X = Window::WINDOW_WIDTH / 2 - ROAD_WIDTH / 2;
	static int constexpr ROAD_TOP_Y = 0;
	static int constexpr ROAD_MIDDLE_X = ROAD_LEFT_X + ROAD_WIDTH / 2;

	static int constexpr ROAD_RIGHT_X = ROAD_LEFT_X + ROAD_WIDTH;
	static int constexpr ROAD_BOTTOM_Y = ROAD_TOP_Y + ROAD_HEIGHT;

	static int const WHITE_LANE_WIDTH = 10;
	static int const WHITE_LANE_HEIGHT = 30;

	static bool checkIfInsideRoad(int x, int y);
	
private:
};

