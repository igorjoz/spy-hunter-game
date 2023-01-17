#pragma once


#include"SDL.h"
#include"Window.h"
#include"PlayerCar.h"
#include"EnemyCar.h"
#include"NeutralCar.h"


class Game
{
public:
	static const int SCORE_INCREMENT = 1;
	static const int PREMIUM_SCORE_INCREMENT = 4;

	Game(SDL* sdl, Window* window);
	~Game();
	void run();
	void restart();
	void resetScore();
	void calculateScore();

	void handleCarsRespawning();
	void handleIsPlayerCollidingWithEnemy();
	void handleIsPlayerCollidingWithNeutral();
	void handleIsPlayerCollidingWithPowerUp();
	void handleHasPlayerShotEnemy();
	void handleHasPlayerShotNeutral();

	bool isPlayerCollidingWithEnemy();
	bool isPlayerCollidingWithNeutral();
	bool isPlayerCollidingWithPowerUp();

	bool hasPlayerShotEnemy();
	bool hasPlayerShotNeutral();

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
	bool getIsScoreFrozen() const;
	bool getIsPowerUpActive() const;
	bool getIsPowerUpUsedUp() const;
	bool getIsGameOver() const;

	void setIsPaused(bool isPaused);
	void setIsGameOver(bool isGameOver);
	
private:
	SDL* sdl;
	Window* window;
	PlayerCar* playerCar;
	EnemyCar* enemyCar;
	NeutralCar* neutralCar;

	int score;
	bool isScoreFrozen;
	bool isPowerUpActive;
	bool isPowerUpUsedUp;
	bool isPaused;
	bool isGameOver;
};

