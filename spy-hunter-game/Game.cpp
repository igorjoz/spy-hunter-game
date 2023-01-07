#include "Game.h"


Game::Game(SDL* sdl, Window* window)
{
	this->sdl = sdl;
	this->window = window;

	this->distance = 0;
	this->etiBMPSpeed = 1;
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