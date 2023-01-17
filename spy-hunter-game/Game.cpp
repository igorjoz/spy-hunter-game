#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"
#include "EnemyCar.h"
#include "NeutralCar.h"
#include "Map.h"
#include "DrawService.h"
#include "PowerUp.h"


Game::Game(SDL* sdl, Window* window) {
	this->sdl = sdl;
	this->window = window;

	this->playerCar = new PlayerCar();
	this->enemyCar = new EnemyCar();
	this->neutralCar = new NeutralCar();

	this->score = 0;
	this->isScoreFrozen = false;
	this->isPowerUpActive = false;
	this->isPowerUpUsedUp = false;
	this->isPaused = false;
	this->isGameOver = false;
}


Game::~Game() {
	delete playerCar;
	delete enemyCar;
	delete neutralCar;
}


void Game::run() {
	PlayerCar* playerCar = getPlayerCar();
	EnemyCar* enemyCar = getEnemyCar();
	NeutralCar* neutralCar = getNeutralCar();
	
	calculateScore();
	
	playerCar->move();

	handleCarsRespawning();

	enemyCar->move();
	
	neutralCar->move();

	handleIsPlayerCollidingWithEnemy();
	handleIsPlayerCollidingWithNeutral();
	handleIsPlayerCollidingWithPowerUp();

	handleHasPlayerShotEnemy();
	handleHasPlayerShotNeutral();
}


void Game::restart() {
	playerCar->resetToStartingPosition();

	resetScore();

	window->resetTime();
}


void Game::resetScore() {
	score = 0;
}


void Game::calculateScore() {
	int verticalVelocity = static_cast<int>(playerCar->getVerticalVelocity());
	int slowVelocity = static_cast<int>(CarSpeed::SLOW);
	MovementDirection playerVerticalMovementDirection = playerCar->getVerticalMovementDirection();
	bool isInsideRoad = Map::checkIfInsideRoad(playerCar->getX(), playerCar->getY());

	if (!isScoreFrozen and isInsideRoad) {
		score += Game::SCORE_INCREMENT;

		if (playerVerticalMovementDirection == MovementDirection::UP) {
			score += Game::PREMIUM_SCORE_INCREMENT;
		}
	}
}


void Game::handleCarsRespawning() {
	int playerCarX = playerCar->getX();
	
	if (enemyCar->getIsDestroyed()) {
		enemyCar->respawn(playerCarX, EnemyCar::STARTING_Y);
	}

	if (neutralCar->getIsDestroyed()) {
		neutralCar->respawn();
	}
}


void Game::handleIsPlayerCollidingWithEnemy() {
	double worldTime = window->getWorldTime();
	double playerProtectionTime = static_cast<double>(Window::PLAYER_PROTECTION_TIME);
	
	if (isPlayerCollidingWithEnemy()) {
		if (worldTime < playerProtectionTime) {
			playerCar->resetToStartingPosition();
		}
		else {
			isGameOver = true;
		}
	}
}


void Game::handleIsPlayerCollidingWithNeutral() {
	if (isPlayerCollidingWithNeutral()) {
		neutralCar->setIsDestroyed(true);
		isScoreFrozen = true;

		int fiveSeconds = Window::FRAME_RATE * 5;
		window->setScoreFreezeTime(fiveSeconds);
	}

	if (isScoreFrozen) {
		window->decreaseScoreFreezeTime();

		if (window->getScoreFreezeTime() <= 0) {
			isScoreFrozen = false;
		}
	}
}


void Game::handleIsPlayerCollidingWithPowerUp() {
	if (isPlayerCollidingWithPowerUp()) {
		isPowerUpActive = true;
		isPowerUpUsedUp = true;

		playerCar->setShootingRange(PlayerCar::SPECIAL_SHOOTING_RANGE);
		playerCar->setBulletsQuantity(PlayerCar::SPECIAL_BULLETS_QUANTITY);

		int tenSeconds = Window::FRAME_RATE * 10;
		window->setPowerUpTime(tenSeconds);
	}

	if (isPowerUpActive) {
		window->decreasePowerUpTime();

		if (window->getPowerUpTime() <= 0) {
			isPowerUpActive = false;
			playerCar->setShootingRange(PlayerCar::REGULAR_SHOOTING_RANGE);
			playerCar->setBulletsQuantity(PlayerCar::REGULAR_BULLETS_QUANTITY);
		}
	}
}


void Game::handleHasPlayerShotEnemy() {
	if (hasPlayerShotEnemy()) {
		enemyCar->setIsDestroyed(true);
	}
}


void Game::handleHasPlayerShotNeutral() {
	if (hasPlayerShotNeutral()) {
		neutralCar->setIsDestroyed(true);
		isScoreFrozen = true;

		int fiveSeconds = Window::FRAME_RATE * 5;
		window->setScoreFreezeTime(fiveSeconds);
	}

	if (isScoreFrozen) {
		window->decreaseScoreFreezeTime();

		if (window->getScoreFreezeTime() == 0) {
			isScoreFrozen = false;
		}
	}
}


bool Game::isPlayerCollidingWithEnemy() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();

	int enemyCarX = enemyCar->getX();
	int enemyCarY = enemyCar->getY();

	if (
		!enemyCar->getIsDestroyed() and
		playerCarX < enemyCarX + Car::WIDTH and
		playerCarX + Car::WIDTH > enemyCarX and
		playerCarY < enemyCarY + Car::HEIGHT and
		playerCarY + Car::HEIGHT > enemyCarY
		) {
		return true;
	}

	return false;
}


bool Game::isPlayerCollidingWithNeutral() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();

	int neutralCarX = neutralCar->getX();
	int neutralCarY = neutralCar->getY();

	if (
		!neutralCar->getIsDestroyed() and
		playerCarX < neutralCarX + Car::WIDTH and
		playerCarX + Car::WIDTH > neutralCarX and
		playerCarY < neutralCarY + Car::HEIGHT and
		playerCarY + Car::HEIGHT > neutralCarY
		) {
		return true;
	}

	return false;
}


bool Game::isPlayerCollidingWithPowerUp() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();

	int powerUpX = PowerUp::X;
	int powerUpY = PowerUp::Y;

	if (
		!isPowerUpUsedUp and
		playerCarX < powerUpX + PowerUp::WIDTH and
		playerCarX + Car::WIDTH > powerUpX and
		playerCarY < powerUpY + PowerUp::HEIGHT and
		playerCarY + Car::HEIGHT > powerUpY
		) {
		return true;
	}

	return false;
}


bool Game::hasPlayerShotEnemy() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();
	int enemyCarX = enemyCar->getX();
	int enemyCarY = enemyCar->getY();
	int shootingRange = playerCar->getShootingRange();
	int horizontalShootingRange = PlayerCar::HORIZONTAL_SHOOTING_RANGE;
	
	if (
		playerCar->getIsShooting() and
		playerCarX + horizontalShootingRange >= enemyCarX and
		playerCarX + horizontalShootingRange <= enemyCarX + Car::WIDTH and
		playerCarY >= enemyCarY and
		playerCarY - shootingRange <= enemyCarY
		) {
		return true;
	}

	return false;
}


bool Game::hasPlayerShotNeutral() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();
	int neutralCarX = neutralCar->getX();
	int neutralCarY = neutralCar->getY();
	int shootingRange = playerCar->getShootingRange();
	int horizontalShootingRange = PlayerCar::HORIZONTAL_SHOOTING_RANGE;

	if (
		playerCar->getIsShooting() and
		playerCarX + horizontalShootingRange >= neutralCarX and
		playerCarX + horizontalShootingRange <= neutralCarX + Car::WIDTH and
		playerCarY >= neutralCarY and
		playerCarY - shootingRange <= neutralCarY
		) {
		return true;
	}

	return false;
}


void Game::handleArrowKeyPressed() {
	playerCar->move();
}


void Game::handleArrowUpKeyPressed() {
	playerCar->setVerticalMovementDirection(MovementDirection::UP);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowDownKeyPressed() {
	playerCar->setVerticalMovementDirection(MovementDirection::DOWN);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowLeftKeyPressed() {
	playerCar->setHorizontalMovementDirection(MovementDirection::LEFT);
	playerCar->setHorizontalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowRightKeyPressed() {
	playerCar->setHorizontalMovementDirection(MovementDirection::RIGHT);
	playerCar->setHorizontalVelocity(CarSpeed::REGULAR);
}


void Game::stopVerticalMovement() {
	playerCar->setVerticalMovementDirection(MovementDirection::NONE);
	playerCar->setVerticalVelocity(CarSpeed::NONE);
}


void Game::stopHorizontalMovement() {
	playerCar->setHorizontalMovementDirection(MovementDirection::NONE);
	playerCar->setHorizontalVelocity(CarSpeed::NONE);
}


// get / set
PlayerCar* Game::getPlayerCar() const {
	return playerCar;
}


EnemyCar* Game::getEnemyCar() const {
	return enemyCar;
}


NeutralCar* Game::getNeutralCar() const {
	return neutralCar;
}


int Game::getScore() const {
	return score;
}


bool Game::getIsPaused() const {
	return isPaused;
}


bool Game::getIsScoreFrozen() const {
	return isScoreFrozen;
}


bool Game::getIsPowerUpActive() const {
	return isPowerUpActive;
}


bool Game::getIsPowerUpUsedUp() const {
	return isPowerUpUsedUp;
}


bool Game::getIsGameOver() const {
	return isGameOver;
}


void Game::setIsPaused(bool isPaused) {
	this->isPaused = isPaused;
}


void Game::setIsGameOver(bool isGameOver) {
	this->isGameOver = isGameOver;
}