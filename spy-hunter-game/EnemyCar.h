#pragma once


#include "Car.h"


class EnemyCar : public Car
{
public:
	static const int STARTING_X = 350;
	static const int STARTING_Y = 250;

	EnemyCar();
};

