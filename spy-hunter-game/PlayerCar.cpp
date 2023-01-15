#include "PlayerCar.h"


#include "Constants.h"


PlayerCar::PlayerCar() {
	this->x = PlayerCar::STARTING_X;
	this->y = PlayerCar::STARTING_Y;

	this->isShooting = false;
}


bool PlayerCar::getIsShooting() const {
	return isShooting;
}


void PlayerCar::setIsShooting(bool isShooting) {
	this->isShooting = isShooting;
}