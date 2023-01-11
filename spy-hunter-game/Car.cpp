#include "Car.h"


#include "Constants.h"
#include "Map.h"
#include "Window.h"


#include <iostream>


Car::Car()
{
	this->x = 0;
	this->y = 0;
	this->speed = CarSpeed::REGULAR;
	this->horizontalVelocity = CarSpeed::NONE;
	this->verticalVelocity = CarSpeed::NONE;

	this->isMoving = false;
	this->movementDirection = MovementDirection::NONE;
	this->horizontalMovementDirection = MovementDirection::NONE;
	this->verticalMovementDirection = MovementDirection::NONE;
}


bool Car::checkIfBelowTopOfWindow()
{
	return y > CAR_HEIGHT / 2;
}


bool Car::checkIfAboveBottomOfWindow()
{
	return y < Window::WINDOW_HEIGHT - CAR_HEIGHT / 2;
}


bool Car::checkIfBeforeLeftSideOfWindow()
{
	return x > CAR_WIDTH / 2;
}


bool Car::checkIfBeforeRightSideOfWindow()
{
	return x < Window::WINDOW_WIDTH - CAR_WIDTH / 2;
}

//bool Car::checkIfWithinWindow()
//{	if (
//		// check of the car is below the top of the screen
//		y > CAR_HEIGHT / 2 and
//		// check if the car is not at the bottom of the screen
//		y < Window::WINDOW_HEIGHT - CAR_HEIGHT / 2 and
//		// check if the car is not at the left side of the screen
//		x > CAR_WIDTH / 2 and
//		// check if the car is not at the right side of the screen
//		x < Window::WINDOW_WIDTH - CAR_WIDTH / 2
//		) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}


bool Car::checkIfInsideRoad()
{
	return Map::checkIfInsideRoad(x, y);
}


void Car::move()
{
	int verticalVelocityValue = static_cast<int>(verticalVelocity);
	int horizontalVelocityValue = static_cast<int>(horizontalVelocity);
		
	if (horizontalVelocity == CarSpeed::NONE and verticalVelocity == CarSpeed::NONE) {
		return;
	}

	printf("horizontalVelocityValue: %d\n", horizontalVelocityValue);
	printf("verticalMovementDirection: %d\n", verticalMovementDirection);
	
	if (verticalVelocityValue) {
		if (verticalMovementDirection == MovementDirection::UP) {
			moveForward();
			//y -= verticalVelocityValue;
		}
		else if (verticalMovementDirection == MovementDirection::DOWN) {
			moveBackward();
			//y += horizontalVelocityValue;
		}
	}
	
	if (horizontalVelocityValue) {
		if (horizontalMovementDirection == MovementDirection::LEFT) {
			moveLeft();
			//x -= horizontalVelocityValue;
		}
		else if (horizontalMovementDirection == MovementDirection::RIGHT) {
			moveRight();
			//x += horizontalVelocityValue;
		}
	}
}


void Car::moveForward()
{
	if (checkIfBelowTopOfWindow()) {
		if (checkIfInsideRoad()) {
			y -= static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			y -= static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveBackward()
{
	if (checkIfAboveBottomOfWindow()) {
		if (checkIfInsideRoad()) {
			y += static_cast<int>(CarSpeed::REGULAR);
		}
		else {
			y += static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveLeft()
{
	if (checkIfBeforeLeftSideOfWindow()) {
		if (checkIfInsideRoad()) {
			x -= static_cast<int>(CarSpeed::SLOW);
		}
		else {
			x -= static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::moveRight()
{
	if (checkIfBeforeRightSideOfWindow()) {
		if (checkIfInsideRoad()) {
			x += static_cast<int>(CarSpeed::SLOW);
		}
		else {
			x += static_cast<int>(CarSpeed::SLOW);
		}
	}
}


void Car::resetMovementDirection()
{
	movementDirection = MovementDirection::NONE;
	verticalMovementDirection = MovementDirection::NONE;
	horizontalMovementDirection = MovementDirection::NONE;
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


void Car::setVerticalMovementDirection(MovementDirection verticalMovementDirection)
{
	this->verticalMovementDirection = verticalMovementDirection;
}


void Car::setHorizontalMovementDirection(MovementDirection horizontalMovementDirection)
{
	this->horizontalMovementDirection = horizontalMovementDirection;
}


void Car::setVerticalVelocity(CarSpeed velocity)
{
	this->verticalVelocity = velocity;
}


void Car::setHorizontalVelocity(CarSpeed velocity)
{
	this->horizontalVelocity = velocity;
}