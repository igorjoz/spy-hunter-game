#pragma once


#include"Constants.h"


class Car
{
public:
	static int const CAR_WIDTH = 50;
	static int const CAR_HEIGHT = 90;

	Car();
	bool checkIfInsideRoad();
	
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	
	int getX();
	int getY();
	CarSpeed getCarSpeed();
	bool getIsMoving();
	MovementDirection getMovementDirection();

	void setX(int x);
	void setY(int y);
	void setIsMoving(bool isMoving);
	void setMovementDirection(MovementDirection movementDirection);
	
protected:
	int x;
	int y;
	CarSpeed speed;
	bool isMoving;
	MovementDirection movementDirection;
};

