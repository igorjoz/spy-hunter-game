#pragma once


#include "Car.h"
#include "Window.h"


class PlayerCar: public Car
{
public:
	const static int STARTING_X = Window::WINDOW_WIDTH / 2;
	const static int STARTING_Y = Window::WINDOW_HEIGHT - 80;

	PlayerCar();
};

