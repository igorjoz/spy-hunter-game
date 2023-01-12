#include "DrawService.h"
#include "Map.h"
#include "Surface.h"
#include "Window.h"


void DrawService::drawGame(SDL* sdl, Game* game) {
	drawRoadside(sdl);
	drawRoad(sdl);
	drawPlayerCar(sdl, game);
	drawEnemyCar(sdl, game);
	drawNeutralCar(sdl, game);
}


void DrawService::drawRoadside(SDL* sdl) {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadsideRectangle;
	roadsideRectangle.x = 0;
	roadsideRectangle.y = 0;
	roadsideRectangle.w = Window::WINDOW_WIDTH;
	roadsideRectangle.h = Window::WINDOW_HEIGHT;

	SDL_FillRect(screenSurface, &roadsideRectangle, SDL_MapRGB(screenSurface->format, 244, 255, 31));
}


void DrawService::drawRoad(SDL* sdl) {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadRectangle;
	roadRectangle.x = Map::ROAD_LEFT_X;
	roadRectangle.y = Map::ROAD_TOP_Y;
	roadRectangle.w = Map::ROAD_WIDTH;
	roadRectangle.h = Map::ROAD_HEIGHT;

	SDL_FillRect(screenSurface, &roadRectangle, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	DrawService::drawDividingLines(sdl);
}


void DrawService::drawDividingLines(SDL* sdl) {
	SDL_Surface* screenSurface = sdl->screen;
	
	for (int i = 0; i < Map::ROAD_HEIGHT; i += Map::WHITE_LANE_HEIGHT * 2) {
		SDL_Rect whiteLaneRectangle;
		whiteLaneRectangle.x = Map::ROAD_MIDDLE_X - Map::WHITE_LANE_WIDTH / 2;
		whiteLaneRectangle.y = i;
		whiteLaneRectangle.w = Map::WHITE_LANE_WIDTH;
		whiteLaneRectangle.h = Map::WHITE_LANE_HEIGHT;

		SDL_FillRect(screenSurface, &whiteLaneRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	}
}


void DrawService::drawPlayerCar(SDL* sdl, Game* game) {
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


void DrawService::drawEnemyCar(SDL* sdl, Game* game) {
	EnemyCar* enemyCar = game->getEnemyCar();
	int x = enemyCar->getX();
	int y = enemyCar->getY();

	Surface::drawSurface(sdl->screen, sdl->enemyCar, x, y);
}


void DrawService::drawNeutralCar(SDL* sdl, Game* game) {
	NeutralCar* neutralCar = game->getNeutralCar();
	int x = neutralCar->getX();
	int y = neutralCar->getY();

	Surface::drawSurface(sdl->screen, sdl->neutralCar, x, y);
}
