#include "NeutralCar.h"


NeutralCar::NeutralCar() {
	this->x = NeutralCar::STARTING_X;
	this->y = NeutralCar::STARTING_Y;
}


void NeutralCar::move() {
	if (y > 0) {
		moveForward();
	}
	else {
		resetToStartingPosition();
	}
}


void NeutralCar::resetToStartingPosition() {
	x = NeutralCar::STARTING_X;
	y = NeutralCar::STARTING_Y;
}