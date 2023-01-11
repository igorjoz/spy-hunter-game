#pragma once


#include"Constants.h"


class Car
{
public:
	static int const CAR_WIDTH = 50;
	static int const CAR_HEIGHT = 90;

	Car();
	bool checkIfBelowTopOfWindow();
	bool checkIfAboveBottomOfWindow();
	bool checkIfBeforeLeftSideOfWindow();
	bool checkIfBeforeRightSideOfWindow();
	//bool checkIfWithinWindow();
	bool checkIfInsideRoad();
	
	void move();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void resetMovementDirection();
	
	int getX();
	int getY();
	CarSpeed getCarSpeed();
	bool getIsMoving();
	MovementDirection getMovementDirection();

	void setX(int x);
	void setY(int y);
	void setIsMoving(bool isMoving);
	void setMovementDirection(MovementDirection movementDirection);
	void setVerticalMovementDirection(MovementDirection verticalMovementDirection);
	void setHorizontalMovementDirection(MovementDirection horizontalMovementDirection);
	void setVerticalVelocity(CarSpeed velocity);
	void setHorizontalVelocity(CarSpeed velocity);
	
protected:
	int x;
	int y;
	CarSpeed speed;
	CarSpeed verticalVelocity;
	CarSpeed horizontalVelocity;
	bool isMoving;
	MovementDirection movementDirection;
	MovementDirection verticalMovementDirection;
	MovementDirection horizontalMovementDirection;
};

