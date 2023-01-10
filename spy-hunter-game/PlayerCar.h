#pragma once


#include"Car.h"


class PlayerCar: public Car
{
public:
	const static int STARTING_X = SCREEN_WIDTH / 2;
	const static int STARTING_Y = SCREEN_HEIGHT - 80;

	PlayerCar();
};

