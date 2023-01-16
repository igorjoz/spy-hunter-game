#include "PlayerCar.h"


#include "Constants.h"


PlayerCar::PlayerCar() {
	this->x = PlayerCar::STARTING_X;
	this->y = PlayerCar::STARTING_Y;

	this->shootingRange = PlayerCar::REGULAR_BULLETS_QUANTITY;
	this->isShooting = false;
}


void PlayerCar::resetToStartingPosition() {
	this->x = PlayerCar::STARTING_X;
	this->y = PlayerCar::STARTING_Y;
}


int PlayerCar::getShootingRange() const {
	return this->shootingRange;
}


bool PlayerCar::getIsShooting() const {
	return isShooting;
}


void PlayerCar::setIsShooting(bool isShooting) {
	this->isShooting = isShooting;
}


void PlayerCar::setShootingRange(int shootingRange) {
	this->shootingRange = shootingRange;
}