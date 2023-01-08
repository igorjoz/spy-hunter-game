#include "Game.h"


#include "Constants.h"
#include "Surface.h"


Game::Game(SDL* sdl, Window* window)
{
	this->sdl = sdl;
	this->window = window;

	this->playerCarX = PLAYER_CAR_STARTING_X;
	this->playerCarY = PLAYER_CAR_STARTING_Y;

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
	int x = this->getPlayerCarX();
	int y = this->getPlayerCarY();
	
	Surface::drawSurface(this->sdl->screen, this->sdl->playerCar, x, y);
}


void Game::handleArrowUpKeyPressed()
{
	this->playerCarY -= static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowDownKeyPressed()
{
	this->playerCarY += static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowLeftKeyPressed()
{
	this->playerCarX -= static_cast<int>(CarSpeed::REGULAR);
}


void Game::handleArrowRightKeyPressed()
{
	this->playerCarX += static_cast<int>(CarSpeed::REGULAR);
}


// get / set
int Game::getPlayerCarX()
{
	return this->playerCarX;
}


int Game::getPlayerCarY()
{
	return this->playerCarY;
}


void Game::setPlayerCarX()
{
	this->playerCarX = 0;
}


void Game::setPlayerCarY()
{
	this->playerCarY = 0;
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