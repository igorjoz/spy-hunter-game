#include "EnemyCar.h"


#include <stdio.h>


EnemyCar::EnemyCar() {
	this->x = EnemyCar::STARTING_X;
	this->y = EnemyCar::STARTING_Y;
}


void EnemyCar::move() {
	if (y > 0) {
		moveForward();
	}
	else {
		resetToStartingPosition();
	}
}


void EnemyCar::resetToStartingPosition() {
	x = EnemyCar::STARTING_X;
	y = EnemyCar::STARTING_Y;
}