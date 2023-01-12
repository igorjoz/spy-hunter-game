#include "Car.h"


#include "Constants.h"
#include "Map.h"
#include "Window.h"


#include <iostream>


Car::Car()
{
	this->x = 0;
	this->y = 0;
	this->horizontalVelocity = CarSpeed::NONE;
	this->verticalVelocity = CarSpeed::NONE;

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

	if (verticalVelocityValue) {
		if (verticalMovementDirection == MovementDirection::UP) {
			moveForward();
		}
		else if (verticalMovementDirection == MovementDirection::DOWN) {
			moveBackward();
		}
	}
	
	if (horizontalVelocityValue) {
		if (horizontalMovementDirection == MovementDirection::LEFT) {
			moveLeft();
		}
		else if (horizontalMovementDirection == MovementDirection::RIGHT) {
			moveRight();
		}
	}
}


void Car::moveForward()
{
	int verticalVelocityValue;

	if (checkIfInsideRoad()) {
		verticalVelocity = CarSpeed::REGULAR;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}
	else {
		verticalVelocity = CarSpeed::SLOW;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}
	
	if (checkIfBelowTopOfWindow()) {
		y -= verticalVelocityValue;
	}
}


void Car::moveBackward()
{
	int verticalVelocityValue;
	
	if (checkIfInsideRoad()) {
		verticalVelocity = CarSpeed::REGULAR;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}
	else {
		verticalVelocity = CarSpeed::SLOW;
		verticalVelocityValue = static_cast<int>(verticalVelocity);
	}
	
	if (checkIfAboveBottomOfWindow()) {
		y += verticalVelocityValue;
	}
}


void Car::moveLeft()
{
	horizontalVelocity = CarSpeed::SLOW;
	int horizontalVelocityValue = static_cast<int>(horizontalVelocity);
	
	if (checkIfBeforeLeftSideOfWindow()) {
		x -= horizontalVelocityValue;
	}
}


void Car::moveRight()
{
	horizontalVelocity = CarSpeed::SLOW;
	int horizontalVelocityValue = static_cast<int>(horizontalVelocity);
	
	if (checkIfBeforeRightSideOfWindow()) {
		x += horizontalVelocityValue;
	}
}


void Car::resetMovementDirection()
{
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


MovementDirection Car::getVerticalMovementDirection()
{
	return verticalMovementDirection;
}


MovementDirection Car::getHorizontalMovementDirection()
{
	return horizontalMovementDirection;
}


CarSpeed Car::getVerticalVelocity()
{
	return verticalVelocity;
}


CarSpeed Car::getHorizontalVelocity()
{
	return horizontalVelocity;
}


void Car::setX(int x)
{
	this->x = x;
}


void Car::setY(int y)
{
	this->y = y;
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