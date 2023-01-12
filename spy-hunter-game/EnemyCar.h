#pragma once


#include "Car.h"


class EnemyCar : public Car
{
public:
	static const int STARTING_X = 100;
	static const int STARTING_Y = 100;

	EnemyCar();
};

