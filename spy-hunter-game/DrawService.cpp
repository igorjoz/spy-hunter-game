#include "DrawService.h"
#include "Map.h"
#include "Surface.h"


void DrawService::drawGame(SDL* sdl, Game* game)
{
	drawRoadside(sdl);
	drawRoad(sdl);
	drawPlayerCar(sdl, game);
}


void DrawService::drawRoadside(SDL* sdl)
{
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadsideRectangle;
	roadsideRectangle.x = 0;
	roadsideRectangle.y = 0;
	roadsideRectangle.w = SCREEN_WIDTH;
	roadsideRectangle.h = SCREEN_HEIGHT;

	SDL_FillRect(screenSurface, &roadsideRectangle, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00));
}


void DrawService::drawRoad(SDL* sdl)
{
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadRectangle;
	roadRectangle.x = Map::ROAD_LEFT_X;
	roadRectangle.y = Map::ROAD_TOP_Y;
	roadRectangle.w = Map::ROAD_WIDTH;
	roadRectangle.h = Map::ROAD_HEIGHT;

	SDL_FillRect(screenSurface, &roadRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
}


void DrawService::drawPlayerCar(SDL* sdl, Game* game)
{
	PlayerCar* playerCar = game->getPlayerCar();
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



	Surface::drawSurface(sdl->screen, sdl->playerCar, x, y);

	/*Surface* playerCarSurface = playerCar->getSurface();
	SDL_Texture* playerCarTexture = playerCarSurface->getTexture();

	SDL_Rect playerCarRect;
	playerCarRect.x = x;
	playerCarRect.y = y;
	playerCarRect.w = CAR_WIDTH;
	playerCarRect.h = CAR_HEIGHT;

	SDL_RenderCopy(this->window->getRenderer(), playerCarTexture, NULL, &playerCarRect);*/
}
