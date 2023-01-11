#include "Car.h"


#include "Constants.h"
#include "Map.h"
#include "Window.h"


Car::Car()
{
	this->x = 0;
	this->y = 0;
	this->speed = CarSpeed::REGULAR;
	this->horizontalVelocity = CarSpeed::NONE;
	this->verticalVelocity = CarSpeed::NONE;

	this->isMoving = false;
	this->movementDirection = MovementDirection::NONE;
}


bool Car::checkIfWithinWindow()
{
	if (
		// check of the car is below the top of the screen
		y > CAR_HEIGHT / 2 and
		// check if the car is not at the bottom of the screen
		y < Window::WINDOW_HEIGHT - CAR_HEIGHT / 2 and
		// check if the car is not at the left side of the screen
		x > CAR_WIDTH / 2 and
		// check if the car is not at the right side of the screen
		x < Window::WINDOW_WIDTH - CAR_WIDTH / 2
		) {
		return true;
	}
	else {
		return false;
	}
}


bool Car::checkIfInsideRoad()
{
	return Map::checkIfInsideRoad(this->x, this->y);
}


void Car::moveForward()
{
	if (checkIfWithinWindow()) {
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
	if (checkIfWithinWindow()) {
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
	if (checkIfWithinWindow()) {
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
	if (checkIfWithinWindow()) {
		if (checkIfInsideRoad()) {
			x += static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			x += static_cast<int>(CarSpeed::SLOW);
		}
	}
}


int Car::getX()
{
	return x;
}


int Car::getY()
{
	return y;
}


CarSpeed Car::getCarSpeed()
{
	return speed;
}


bool Car::getIsMoving() {
	return isMoving;
}


MovementDirection Car::getMovementDirection()
{
	return movementDirection;
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