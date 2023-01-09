#pragma once


class Car
{
public:
	int getX();
	int getY();
	bool getIsMoving();

	void setX(int x);
	void setY(int y);
	void setIsMoving(bool isMoving);

	// get / set
	/*int getSpeed();
	int getAcceleration();
	int getBrake();
	int getTurnSpeed();
	int getTurnAcceleration();
	int getTurnBrake();
	int getTurn();
	int getTurnDirection();
	int getTurnDirectionAcceleration();
	int getTurnDirectionBrake();
	int getTurnDirectionTurnSpeed();
	int getTurnDirectionTurnAcceleration();
	int getTurnDirectionTurnBrake();
	int getTurnDirectionTurn();
	int getTurnDirectionTurnDirection();
	int getTurnDirectionTurnDirectionAcceleration();
	int getTurnDirectionTurnDirectionBrake();
	int getTurnDirectionTurnDirectionTurnSpeed();
	int getTurnDirectionTurnDirectionTurnAcceleration();
	int getTurnDirectionTurnDirectionTurnBrake();
	int getTurnDirectionTurnDirectionTurn();
	int getTurnDirectionTurnDirectionTurnDirection();

	void setSpeed(int speed);
	void setAcceleration(int acceleration);
	void setBrake(int brake);
	void setTurnSpeed(int turnSpeed);
	void setTurnAcceleration(int turnAcceleration);
	void setTurnBrake(int turnBrake);
	void setTurn(int turn);
	void setTurnDirection(int turnDirection);
	void setTurnDirectionAcceleration(int turnDirectionAcceleration);
	void setTurnDirectionBrake(int turnDirectionBrake);
	void setTurnDirectionTurnSpeed(int turnDirectionTurnSpeed);
	void setTurnDirectionTurnAcceleration(int turnDirectionTurnAcceleration);
	void setTurnDirectionTurnBrake(int turnDirectionTurnBrake);
	void setTurnDirectionTurn(int turnDirectionTurn);
	void setTurnDirectionTurnDirection(int turnDirectionTurnDirection);
	void setTurnDirectionTurnDirectionAcceleration(int turnDirectionTurnDirectionAcceleration);
	void setTurnDirectionTurnDirectionBrake(int turnDirectionTurnDirectionBrake);
	void setTurnDirectionTurnDirectionTurnSpeed(int turnDirectionTurnDirectionTurnSpeed);
	void setTurnDirectionTurnDirectionTurnAcceleration(int turnDirectionTurnDirectionTurnAcceleration);
	void setTurnDirectionTurnDirectionTurnBrake(int turnDirectionTurnDirectionTurnBrake);
	void setTurnDirectionTurnDirectionTurn(int turnDirectionTurnDirectionTurn);
	void setTurnDirectionTurnDirectionTurnDirection(int turnDirectionTurnDirectionTurnDirection);*/
	
protected:
	int x;
	int y;
	bool isMoving;
};

