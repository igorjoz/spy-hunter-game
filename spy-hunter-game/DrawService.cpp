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
	drawNeutralCar();
	drawEnemyCar();
	drawPlayerCar();
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

	PlayerCar* playerCar = game->getPlayerCar();
	int playerCarVerticalVelocity = static_cast<int>(playerCar->getVerticalVelocity()) + 1;
	
	for (int i = -worldTime * 100 * playerCarVerticalVelocity; i < Map::ROAD_HEIGHT + worldTime * 100 * playerCarVerticalVelocity; i += Map::WHITE_LANE_HEIGHT * 2) {
		SDL_Rect whiteLineRectangle;
		whiteLineRectangle.x = Map::ROAD_MIDDLE_X - Map::WHITE_LANE_WIDTH / 2;
		//whiteLineRectangle.y = -i * playerCarVerticalVelocity + Window::WINDOW_HEIGHT;
		whiteLineRectangle.y = -i + Window::WINDOW_HEIGHT;
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


void DrawService::drawPlayerCarBorder() {
	SDL_Surface* screenSurface = sdl->screen;

	PlayerCar* playerCar = game->getPlayerCar();
	int x = playerCar->getX();
	int y = playerCar->getY();

	SDL_Rect playerCarBorderRectangle;
	playerCarBorderRectangle.x = x;
	playerCarBorderRectangle.y = y;
	playerCarBorderRectangle.w = Car::CAR_WIDTH;
	playerCarBorderRectangle.h = Car::CAR_HEIGHT;

	SDL_FillRect(screenSurface, &playerCarBorderRectangle, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00));

	// if collision with enemy car is detected, draw a red border around the player car
	if (game->isPlayerCollidingWithEnemy()) {
		SDL_FillRect(screenSurface, &playerCarBorderRectangle, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
	}
}


void DrawService::drawEnemyCar() {
	SDL_Surface* screenSurface = sdl->screen;
	
	EnemyCar* enemyCar = game->getEnemyCar();
	int x = enemyCar->getX();
	int y = enemyCar->getY();

	SDL_Rect enemyCarRectangle;
	enemyCarRectangle.x = x;
	enemyCarRectangle.y = y;
	enemyCarRectangle.w = Car::CAR_WIDTH;
	enemyCarRectangle.h = Car::CAR_HEIGHT;

	SDL_BlitSurface(sdl->enemyCar, NULL, screenSurface, &enemyCarRectangle);
	
	//Surface::drawSurface(sdl->screen, sdl->enemyCar, x, y);
}


void DrawService::drawNeutralCar() {
	SDL_Surface* screenSurface = sdl->screen;
	
	NeutralCar* neutralCar = game->getNeutralCar();
	int x = neutralCar->getX();
	int y = neutralCar->getY();

	SDL_Rect neutralCarRectangle;
	neutralCarRectangle.x = x;
	neutralCarRectangle.y = y;
	neutralCarRectangle.w = Car::CAR_WIDTH;
	neutralCarRectangle.h = Car::CAR_HEIGHT;

	SDL_BlitSurface(sdl->neutralCar, NULL, screenSurface, &neutralCarRectangle);

	//Surface::drawSurface(sdl->screen, sdl->neutralCar, x, y);
}
