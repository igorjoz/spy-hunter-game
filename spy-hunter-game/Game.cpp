#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"
#include "Map.h"
#include "DrawService.h"


Game::Game(SDL* sdl, Window* window)
{
	this->sdl = sdl;
	this->window = window;

	this->playerCar = new PlayerCar();

	this->score = 0;
}


Game::~Game()
{
	delete playerCar;
}


void Game::run()
{
	PlayerCar* playerCar = this->getPlayerCar();
	bool isMoving = playerCar->getIsMoving();
	MovementDirection movementDirection = playerCar->getMovementDirection();

	playerCar->move();

	/*if (isMoving) {
		playerCar->move();*/

		/*if (movementDirection == MovementDirection::UP) {
			playerCar->moveForward();
		}
		else if (movementDirection == MovementDirection::DOWN) {
			playerCar->moveBackward();
		}
		else if (movementDirection == MovementDirection::LEFT) {
			playerCar->moveLeft();
		}
		else if (movementDirection == MovementDirection::RIGHT) {
			playerCar->moveRight();
		}*/
	//}

	DrawService::drawGame(sdl, this);
}


void Game::handleArrowKeyPressed()
{
	playerCar->setIsMoving(true);
	playerCar->move();
}


void Game::handleArrowUpKeyPressed()
{
	playerCar->setMovementDirection(MovementDirection::UP);
	playerCar->setVerticalMovementDirection(MovementDirection::UP);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowDownKeyPressed()
{
	playerCar->setMovementDirection(MovementDirection::DOWN);
	playerCar->setVerticalMovementDirection(MovementDirection::DOWN);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowLeftKeyPressed()
{
	playerCar->setMovementDirection(MovementDirection::LEFT);
	playerCar->setHorizontalMovementDirection(MovementDirection::LEFT);
	playerCar->setHorizontalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowRightKeyPressed()
{
	playerCar->setMovementDirection(MovementDirection::RIGHT);
	playerCar->setHorizontalMovementDirection(MovementDirection::RIGHT);
	playerCar->setHorizontalVelocity(CarSpeed::REGULAR);
}


void Game::handleKeyUp()
{
	playerCar->setIsMoving(false);
	playerCar->resetMovementDirection();
}


// get / set
PlayerCar* Game::getPlayerCar()
{
	return playerCar;
}


int Game::getScore()
{
	return score;
}