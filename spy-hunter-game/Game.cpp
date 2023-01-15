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
}


Game::~Game() {
	delete playerCar;
	delete enemyCar;
	delete neutralCar;
}


void Game::run() {
	PlayerCar* playerCar = getPlayerCar();
	EnemyCar* enemyCar = getEnemyCar();
	
	calculateScore();
	
	playerCar->move();

	if (isPlayerCollidingWithEnemy()) {
		//restart();
	}

	if (hasPlayerShotEnemy()) {
		enemyCar->setIsDestroyed(true);
	}

	if (hasPlayerShotNeutral()) {
		neutralCar->setIsDestroyed(true);
		isScoreFrozen = true;
		window->setScoreFreezeTime(Window::FRAME_RATE * 5);
	}

	if (isScoreFrozen) {
		window->decreaseScoreFreezeTime();
		
		if (window->getScoreFreezeTime() == 0) {
			isScoreFrozen = false;
		}
	}

	if (isPlayerCollidingWithPowerUp()) {
		isPowerUpActive = true;
		isPowerUpUsedUp = true;

		window->setScoreFreezeTime(Window::FRAME_RATE * 10);

		playerCar->setShootingRange(PlayerCar::SPECIAL_BULLETS_QUANTITY);
	}

	if (isPowerUpActive) {
		window->decreasePowerUpTime();

		if (window->getPowerUpTime() == 0) {
			isPowerUpActive = false;
			playerCar->setShootingRange(PlayerCar::REGULAR_BULLETS_QUANTITY);
		}
	}
}


void Game::restart() {
	delete playerCar;

	playerCar = new PlayerCar();

	score = 0;

	window->resetTime();
}


void Game::calculateScore() {
	int verticalVelocity = static_cast<int>(playerCar->getVerticalVelocity());
	int slowVelocity = static_cast<int>(CarSpeed::SLOW);
	MovementDirection playerVerticalMovementDirection = playerCar->getVerticalMovementDirection();

	if (
		!isScoreFrozen and
		verticalVelocity > slowVelocity and
		playerVerticalMovementDirection == MovementDirection::UP
		) {
		this->score++;
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


bool Game::isPlayerCollidingWithPowerUp() {
	int playerCarX = playerCar->getX();
	int playerCarY = playerCar->getY();

	if (
		!isPowerUpUsedUp and
		playerCarX < PowerUp::X + PowerUp::WIDTH and
		playerCarX + PowerUp::WIDTH > PowerUp::X and
		playerCarY < PowerUp::Y + PowerUp::HEIGHT and
		playerCarY + PowerUp::HEIGHT > PowerUp::Y
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
		playerCarY + shootingRange >= enemyCarY
		
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
		playerCarX + horizontalShootingRange <= neutralCarX + Car::WIDTH
		and
		playerCarY >= neutralCarY + Car::HEIGHT
		and 
		playerCarY + shootingRange <= neutralCarY + Car::HEIGHT
		//playerCarY + shootingRange >= neutralCarY
		//and 
		//playerCarY + shootingRange >= neutralCarY - Car::HEIGHT
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


void Game::setIsPaused(bool isPaused) {
	this->isPaused = isPaused;
}