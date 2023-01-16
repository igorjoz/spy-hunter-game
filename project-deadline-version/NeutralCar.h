#pragma once


#include "Car.h"
#include "Map.h"


class NeutralCar : public Car
{
public:
	static const int STARTING_X = 150;
	static const int STARTING_Y = Map::ROAD_BOTTOM_Y;

	NeutralCar();

	void move();
	void resetToStartingPosition();
};

