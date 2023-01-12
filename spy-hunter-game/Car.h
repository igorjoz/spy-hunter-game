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
	bool checkIfInsideRoad();
	
	void move();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void resetMovementDirection();
	
	int getX() const;
	int getY() const;
	MovementDirection getVerticalMovementDirection() const;
	MovementDirection getHorizontalMovementDirection() const;
	CarSpeed getVerticalVelocity() const;
	CarSpeed getHorizontalVelocity() const;

	void setX(int x);
	void setY(int y);
	void setVerticalMovementDirection(MovementDirection verticalMovementDirection);
	void setHorizontalMovementDirection(MovementDirection horizontalMovementDirection);
	void setVerticalVelocity(CarSpeed velocity);
	void setHorizontalVelocity(CarSpeed velocity);
	
protected:
	int x;
	int y;
	CarSpeed verticalVelocity;
	CarSpeed horizontalVelocity;
	MovementDirection verticalMovementDirection;
	MovementDirection horizontalMovementDirection;
};

