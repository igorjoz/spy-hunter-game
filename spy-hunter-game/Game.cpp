#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"
#include "EnemyCar.h"
#include "NeutralCar.h"
#include "Map.h"
#include "DrawService.h"


Game::Game(SDL* sdl, Window* window) {
	this->sdl = sdl;
	this->window = window;

	this->playerCar = new PlayerCar();
	this->enemyCar = new EnemyCar();
	this->neutralCar = new NeutralCar();

	this->score = 0;
}


Game::~Game() {
	delete playerCar;
}


void Game::run() {
	calculateScore();
	
	this->getPlayerCar()->move();
}


void Game::restart() {
	delete playerCar;

	playerCar = new PlayerCar();

	score = 0;
}


void Game::calculateScore() {
	int verticalVelocity = static_cast<int>(playerCar->getVerticalVelocity());
	int slowVelocity = static_cast<int>(CarSpeed::SLOW);
	MovementDirection playerVerticalMovementDirection = playerCar->getVerticalMovementDirection();

	if (verticalVelocity > slowVelocity and playerVerticalMovementDirection == MovementDirection::UP) {
		this->score++;
	}
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