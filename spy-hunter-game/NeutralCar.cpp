#include "NeutralCar.h"


NeutralCar::NeutralCar() {
	this->x = NeutralCar::STARTING_X;
	this->y = NeutralCar::STARTING_Y;
}


void NeutralCar::move() {
	if (y > -NeutralCar::HEIGHT) {
		moveForward();
	}
	else {
		resetToStartingPosition();
	}
}


void NeutralCar::moveForward() {
	int verticalVelocityValue;

	if (checkIfInsideRoad()) {
		verticalVelocity = CarSpeed::REGULAR;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}
	else {
		verticalVelocity = CarSpeed::SLOW;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}

	y -= verticalVelocityValue;
}


void NeutralCar::resetToStartingPosition() {
	x = NeutralCar::STARTING_X;
	y = NeutralCar::STARTING_Y;
}