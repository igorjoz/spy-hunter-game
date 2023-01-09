#include "Car.h"

int Car::getX()
{
	return this->x;
}


int Car::getY()
{
	return this->y;
}


bool Car::getIsMoving() {
	return this->isMoving;
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