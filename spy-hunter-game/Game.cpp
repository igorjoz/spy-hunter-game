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

	playerCar->move();

	DrawService::drawGame(sdl, this);
}


void Game::handleArrowKeyPressed()
{
	playerCar->setIsMoving(true);
	playerCar->move();
}


void Game::handleArrowUpKeyPressed()
{
	playerCar->setVerticalMovementDirection(MovementDirection::UP);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowDownKeyPressed()
{
	playerCar->setVerticalMovementDirection(MovementDirection::DOWN);
	playerCar->setVerticalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowLeftKeyPressed()
{
	playerCar->setHorizontalMovementDirection(MovementDirection::LEFT);
	playerCar->setHorizontalVelocity(CarSpeed::REGULAR);
}


void Game::handleArrowRightKeyPressed()
{
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