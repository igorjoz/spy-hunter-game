#include "PlayerCar.h"

#include "Constants.h"

PlayerCar::PlayerCar()
{
	this->x = PLAYER_CAR_STARTING_X;
	this->y = PLAYER_CAR_STARTING_Y;

	this->isMoving = false;

	/*this->width = 0;
	this->height = 0;
	this->speed = 0;
	this->direction = 0;*/
}