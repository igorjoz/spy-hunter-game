#pragma once


#include"Constants.h"


class Car
{
public:
	static int const WIDTH = 50;
	static int const HEIGHT = 90;

	Car();
	bool checkIfBelowTopOfWindow();
	bool checkIfAboveBottomOfWindow();
	bool checkIfBeforeLeftSideOfWindow();
	bool checkIfBeforeRightSideOfWindow();
	bool checkIfInsideRoad();

	//bool checkIfCollidingWith(Car& otherCar);
	
	void move();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void resetMovementDirection();
	void resetToStartingPosition();
	
	int getX() const;
	int getY() const;
	bool getIsDestroyed() const;
	
	MovementDirection getVerticalMovementDirection() const;
	MovementDirection getHorizontalMovementDirection() const;
	CarSpeed getVerticalVelocity() const;
	CarSpeed getHorizontalVelocity() const;

	void setX(int x);
	void setY(int y);
	void setIsDestroyed(bool isDestroyed);
	
	void setVerticalMovementDirection(MovementDirection verticalMovementDirection);
	void setHorizontalMovementDirection(MovementDirection horizontalMovementDirection);
	void setVerticalVelocity(CarSpeed velocity);
	void setHorizontalVelocity(CarSpeed velocity);
	
protected:
	int x;
	int y;
	bool isDestroyed;

	CarSpeed verticalVelocity;
	CarSpeed horizontalVelocity;
	MovementDirection verticalMovementDirection;
	MovementDirection horizontalMovementDirection;
};

