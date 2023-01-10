#include "Game.h"


#include "Constants.h"
#include "Surface.h"
#include "PlayerCar.h"
#include "Map.h"


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
	distance += etiBMPSpeed * delta;

	return distance;
}


void Game::run()
{
	PlayerCar* playerCar = this->getPlayerCar();
	bool isMoving = playerCar->getIsMoving();
	MovementDirection movementDirection = playerCar->getMovementDirection();

	if (isMoving) {
		if (movementDirection == MovementDirection::UP) {
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
		}
	}

	this->drawRoadside();
	this->drawRoad();
	this->drawPlayerCar();
}


void Game::drawRoadside()
{
	SDL_Surface* screenSurface = this->sdl->screen;

	SDL_Rect roadsideRectangle;
	roadsideRectangle.x = 0;
	roadsideRectangle.y = 0;
	roadsideRectangle.w = SCREEN_WIDTH;
	roadsideRectangle.h = SCREEN_HEIGHT;

	SDL_FillRect(screenSurface, &roadsideRectangle, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00));
}


void Game::drawRoad()
{
	SDL_Surface* screenSurface = this->sdl->screen;

	SDL_Rect roadRectangle;
	roadRectangle.x = Map::ROAD_LEFT_X;
	roadRectangle.y = Map::ROAD_TOP_Y;
	roadRectangle.w = Map::ROAD_WIDTH;
	roadRectangle.h = Map::ROAD_HEIGHT;
		
	SDL_FillRect(screenSurface, &roadRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
}


void Game::drawPlayerCar()
{
	PlayerCar* playerCar = this->getPlayerCar();
	int x = playerCar->getX();
	int y = playerCar->getY();

	//SDL_Rect textureRectangle;
	//textureRectangle.x = 0;  //the x coordinate
	//textureRectangle.y = 0; // the y coordinate
	//textureRectangle.w = 50; //the width of the texture
	//textureRectangle.h = 50;

	//SDL_Rect destinationRectangle;
	//destinationRectangle.x = x;
	//destinationRectangle.y = y;
	//destinationRectangle.w = 50;
	//destinationRectangle.h = 50;
	
	//SDL_Texture* playerCarTexture = this->sdl->playerCarTexture;

	//SDL_RenderCopy(sdl->renderer, playerCarTexture, &textureRectangle, &destinationRectangle);
	
	//SDL_RenderPresent(sdl->renderer);


	
	Surface::drawSurface(this->sdl->screen, this->sdl->playerCar, x, y);

	/*Surface* playerCarSurface = playerCar->getSurface();
	SDL_Texture* playerCarTexture = playerCarSurface->getTexture();

	SDL_Rect playerCarRect;
	playerCarRect.x = x;
	playerCarRect.y = y;
	playerCarRect.w = CAR_WIDTH;
	playerCarRect.h = CAR_HEIGHT;

	SDL_RenderCopy(this->window->getRenderer(), playerCarTexture, NULL, &playerCarRect);*/
}


void Game::handleArrowKeyPressed()
{
	this->playerCar->setIsMoving(true);
}


void Game::handleArrowUpKeyPressed()
{
	this->playerCar->setMovementDirection(MovementDirection::UP);
}


void Game::handleArrowDownKeyPressed()
{
	this->playerCar->setMovementDirection(MovementDirection::DOWN);
}


void Game::handleArrowLeftKeyPressed()
{
	this->playerCar->setMovementDirection(MovementDirection::LEFT);
}


void Game::handleArrowRightKeyPressed()
{
	this->playerCar->setMovementDirection(MovementDirection::RIGHT);
}


void Game::handleKeyUp()
{
	this->getPlayerCar()->setIsMoving(false);
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