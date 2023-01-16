#pragma once


#include "Car.h"
#include "Map.h"


class EnemyCar : public Car
{
public:
	static const int STARTING_X = 380;
	static const int STARTING_Y = Map::ROAD_BOTTOM_Y;

	EnemyCar();

	void move();
	void moveForward();
	
	void respawn();
	void resetToStartingPosition();
	void resetPosition();
};

