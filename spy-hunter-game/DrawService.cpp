#include "DrawService.h"


#include "SDL.h"
#include "Window.h"
#include "Game.h"
#include "Map.h"
#include "Surface.h"


SDL* DrawService::sdl = nullptr;
Window* DrawService::window = nullptr;
Game* DrawService::game = nullptr;


void DrawService::initialize(SDL* sdlObject, Window* windowObject, Game* gameObject) {
	sdl = sdlObject;
	window = windowObject;
	game = gameObject;
}


void DrawService::drawGame() {
	drawRoadside();
	drawRoad();
	drawCars();
}


void DrawService::drawCars() {
	drawPlayerCar();
	drawEnemyCar();
	drawNeutralCar();
}


void DrawService::drawRoadside() {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadsideRectangle;
	roadsideRectangle.x = 0;
	roadsideRectangle.y = 0;
	roadsideRectangle.w = Window::WINDOW_WIDTH;
	roadsideRectangle.h = Window::WINDOW_HEIGHT;

	SDL_FillRect(screenSurface, &roadsideRectangle, SDL_MapRGB(screenSurface->format, 244, 255, 31));
}


void DrawService::drawRoad() {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect roadRectangle;
	roadRectangle.x = Map::ROAD_LEFT_X;
	roadRectangle.y = Map::ROAD_TOP_Y;
	roadRectangle.w = Map::ROAD_WIDTH;
	roadRectangle.h = Map::ROAD_HEIGHT;

	SDL_FillRect(screenSurface, &roadRectangle, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	DrawService::drawDividingLines();
}


void DrawService::drawDividingLines() {
	SDL_Surface* screenSurface = sdl->screen;
	double worldTime = window->getWorldTime();
	
	for (int i = 0; i < Map::ROAD_HEIGHT; i += Map::WHITE_LANE_HEIGHT * 2) {
		int y = i + worldTime * 50;

		SDL_Rect whiteLineRectangle;
		whiteLineRectangle.x = Map::ROAD_MIDDLE_X - Map::WHITE_LANE_WIDTH / 2;
		whiteLineRectangle.y = y;
		whiteLineRectangle.w = Map::WHITE_LANE_WIDTH;
		whiteLineRectangle.h = Map::WHITE_LANE_HEIGHT;

		SDL_FillRect(screenSurface, &whiteLineRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	}
}


void DrawService::drawPlayerCar() {
	drawPlayerCarBorder();
	
	SDL_Surface* screenSurface = sdl->screen;
	
	PlayerCar* playerCar = game->getPlayerCar();
	int x = playerCar->getX();
	int y = playerCar->getY();

	SDL_Rect playerCarRectangle;
	playerCarRectangle.x = x;
	playerCarRectangle.y = y;
	playerCarRectangle.w = Car::CAR_WIDTH;
	playerCarRectangle.h = Car::CAR_HEIGHT;
	
	SDL_BlitSurface(sdl->playerCar, NULL, screenSurface, &playerCarRectangle);
}

	/*SDL_Rect playerCarRectangle;
	playerCarRectangle.x = x;
	playerCarRectangle.y = y;
	playerCarRectangle.w = Car::CAR_WIDTH;
	playerCarRectangle.h = Car::CAR_HEIGHT;

	SDL_Rect destinationRectangle;
	destinationRectangle.x = x;
	destinationRectangle.y = y;
	destinationRectangle.w = 50;
	destinationRectangle.h = 50;

	SDL_Texture* playerCarTexture = sdl->playerCarTexture;

	SDL_RenderCopy(sdl->renderer, playerCarTexture, &playerCarRectangle, &destinationRectangle);

	SDL_RenderPresent(sdl->renderer);*/



	//Surface::drawSurface(sdl->screen, sdl->playerCar, x, y);


	
	/*Surface* playerCarSurface = playerCar->getSurface();
	SDL_Texture* playerCarTexture = playerCarSurface->getTexture();

	

	SDL_RenderCopy(this->window->getRenderer(), playerCarTexture, NULL, &playerCarRect);*/
//}


void DrawService::drawPlayerCarBorder() {
	SDL_Surface* screenSurface = sdl->screen;

	PlayerCar* playerCar = game->getPlayerCar();
	int x = playerCar->getX();
	int y = playerCar->getY();

	SDL_Rect playerCarBorderRectangle;
	playerCarBorderRectangle.x = x - 1;
	playerCarBorderRectangle.y = y - 1;
	playerCarBorderRectangle.w = Car::CAR_WIDTH + 2;
	playerCarBorderRectangle.h = Car::CAR_HEIGHT + 2;

	SDL_FillRect(screenSurface, &playerCarBorderRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
}


void DrawService::drawEnemyCar() {
	EnemyCar* enemyCar = game->getEnemyCar();
	int x = enemyCar->getX();
	int y = enemyCar->getY();

	Surface::drawSurface(sdl->screen, sdl->enemyCar, x, y);
}


void DrawService::drawNeutralCar() {
	NeutralCar* neutralCar = game->getNeutralCar();
	int x = neutralCar->getX();
	int y = neutralCar->getY();

	Surface::drawSurface(sdl->screen, sdl->neutralCar, x, y);
}
