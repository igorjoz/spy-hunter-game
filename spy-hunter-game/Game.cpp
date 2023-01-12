#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"
#include "Map.h"
#include "DrawService.h"


Game::Game(SDL* sdl, Window* window) {
	this->sdl = sdl;
	this->window = window;

	this->playerCar = new PlayerCar();

	this->score = 0;
}


Game::~Game() {
	delete playerCar;
}


void Game::run() {
	PlayerCar* playerCar = this->getPlayerCar();
	
	calculateScore();
	
	playerCar->move();

	DrawService::drawGame(sdl, this);
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


int Game::getScore() const {
	return score;
}