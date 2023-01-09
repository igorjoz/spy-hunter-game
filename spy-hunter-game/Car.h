#pragma once


#include"Constants.h"


class Car
{
public:
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

