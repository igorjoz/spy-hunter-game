#include "Map.h"


bool Map::checkIfInsideRoad(int x, int y)
{
	if (x >= ROAD_LEFT_X and x <= ROAD_RIGHT_X and y >= ROAD_TOP_Y and y <= ROAD_BOTTOM_Y) {
		return true;
	}
	else {
		return false;
	}
}