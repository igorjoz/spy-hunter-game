#pragma once


#include "Car.h"
#include "Window.h"


class PlayerCar: public Car
{
public:
	const static int STARTING_X = Window::WIDTH / 2 - Car::WIDTH / 2;
	const static int STARTING_Y = Window::HEIGHT - Car::HEIGHT - 50;

	PlayerCar();

	// get / set
	bool getIsShooting() const;
	void setIsShooting(bool isShooting);

private:
	bool isShooting;
};

