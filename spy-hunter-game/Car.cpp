#include "Car.h"


#include "Constants.h"
#include "Map.h"


Car::Car()
{
	this->x = 0;
	this->y = 0;
	this->speed = CarSpeed::REGULAR;

	this->isMoving = false;
	this->movementDirection = MovementDirection::NONE;
}


bool Car::checkIfInsideRoad()
{
	if (Map::checkIfInsideRoad(this->x, this->y)) {
		return true;
	}
	else {
		return false;
	}
}


void Car::moveForward()
{
	// check of the car is below the top of the screen
	if (this->y > CAR_HEIGHT / 2) {
		if (this->checkIfInsideRoad()) {
			this->y -= static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			this->y -= static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveBackward()
{
	// check if the car is not at the bottom of the screen
	if (this->y < SCREEN_HEIGHT - CAR_HEIGHT / 2) {
		if (this->checkIfInsideRoad()) {
			this->y += static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			this->y += static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveLeft()
{
	// check if the car is not at the left side of the screen
	if (this->x > CAR_WIDTH / 2) {
		if (this->checkIfInsideRoad()) {
			this->x -= static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			this->x -= static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveRight()
{
	// check if the car is not at the right side of the screen
	if (this->x < SCREEN_WIDTH - CAR_WIDTH / 2) {
		if (this->checkIfInsideRoad()) {
			this->x += static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			this->x += static_cast<int>(CarSpeed::SLOW);
		}
	}
}


int Car::getX()
{
	return this->x;
}


int Car::getY()
{
	return this->y;
}


CarSpeed Car::getCarSpeed()
{
	return this->speed;
}


bool Car::getIsMoving() {
	return this->isMoving;
}


MovementDirection Car::getMovementDirection()
{
	return this->movementDirection;
}


void Car::setX(int x)
{
	this->x = x;
}


void Car::setY(int y)
{
	this->y = y;
}


void Car::setIsMoving(bool isMoving)
{
	this->isMoving = isMoving;
}


void Car::setMovementDirection(MovementDirection movementDirection)
{
	this->movementDirection = movementDirection;
}