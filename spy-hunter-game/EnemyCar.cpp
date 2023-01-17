#include "EnemyCar.h"


#include <stdio.h>


EnemyCar::EnemyCar() {
	this->x = EnemyCar::STARTING_X;
	this->y = EnemyCar::STARTING_Y;
}


void EnemyCar::move() {
	if (y > -EnemyCar::HEIGHT) {
		moveForward();
	}
	else {
		resetToStartingPosition();
	}
}


void EnemyCar::moveForward() {
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


void EnemyCar::respawn(int x, int y) {
	resetPosition(x, y);
	isDestroyed = false;
}


void EnemyCar::resetToStartingPosition() {
	x = EnemyCar::STARTING_X;
	y = EnemyCar::STARTING_Y;
}


void EnemyCar::resetPosition(int x, int y) {
	this->x = x;
	this->y = y;
}