#pragma once


#include"SDL.h"
#include"Window.h"
#include"PlayerCar.h"
#include"EnemyCar.h"
#include"NeutralCar.h"


class Game
{
public:
	Game(SDL* sdl, Window* window);
	~Game();
	void run();
	void restart();
	void calculateScore();

	bool isPlayerCollidingWithEnemy();

	void handleArrowKeyPressed();
	void handleArrowUpKeyPressed();
	void handleArrowDownKeyPressed();
	void handleArrowLeftKeyPressed();
	void handleArrowRightKeyPressed();

	void stopVerticalMovement();
	void stopHorizontalMovement();
	
	// get / set
	PlayerCar* getPlayerCar() const;
	EnemyCar* getEnemyCar() const;
	NeutralCar* getNeutralCar() const;
	
	int getScore() const;
	bool getIsPaused() const;

	void setIsPaused(bool isPaused);
	
private:
	SDL* sdl;
	Window* window;
	PlayerCar* playerCar;
	EnemyCar* enemyCar;
	NeutralCar* neutralCar;

	int score;
	bool isPaused;
};

