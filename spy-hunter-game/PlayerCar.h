#pragma once


#include "Car.h"
#include "Window.h"
#include "Bullet.h"


class PlayerCar: public Car
{
public:
	const static int STARTING_X = Window::WIDTH / 2 - Car::WIDTH / 2;
	const static int STARTING_Y = Window::HEIGHT - Car::HEIGHT - 50;

	const static int REGULAR_BULLETS_QUANTITY = 5;
	const static int SPECIAL_BULLETS_QUANTITY = 10;
	
	const static int HORIZONTAL_SHOOTING_RANGE = Bullet::WIDTH * 2 + Bullet::OFFSET * 3;

	PlayerCar();

	void resetToStartingPosition();

	// get / set
	bool getIsShooting() const;
	int getShootingRange() const;

	void setIsShooting(bool isShooting);
	void setShootingRange(int shootingRange);

private:
	int shootingRange;
	bool isShooting;
};

