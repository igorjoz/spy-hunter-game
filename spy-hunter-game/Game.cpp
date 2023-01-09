#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"


Game::Game(SDL* sdl, Window* window)
{
	this->sdl = sdl;
	this->window = window;

	this->playerCar = new PlayerCar();

	this->distance = 0;
	this->etiBMPSpeed = 1;

	
}


double Game::calculateDistance(double delta)
{
	this->distance += etiBMPSpeed * delta;

	return this->distance;
}


void Game::run()
{
	int x = this->getPlayerCar()->getX();
	int y = this->getPlayerCar()->getY();
	
	Surface::drawSurface(this->sdl->screen, this->sdl->playerCar, x, y);
}


void Game::handleArrowUpKeyPressed()
{
	this->getPlayerCar()->setIsMoving(true);
	
	//this->playerCarY -= static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowDownKeyPressed()
{
	//this->playerCarY += static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowLeftKeyPressed()
{
	//this->playerCarX -= static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowRightKeyPressed()
{
	//this->playerCarX += static_cast<int>(CarSpeed::REGULAR);
}


// get / set
PlayerCar* Game::getPlayerCar()
{
	return this->playerCar;
}


double Game::getDistance()
{
	return this->distance;
}


double Game::getEtiBMPSpeed()
{
	return this->etiBMPSpeed;
}


void Game::setDistance(double distance)
{
	this->distance = distance;
}


void Game::setEtiBMPSpeed(double etiBMPSpeed)
{
	this->etiBMPSpeed = etiBMPSpeed;
}