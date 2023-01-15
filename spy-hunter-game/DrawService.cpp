#include "DrawService.h"


#include "SDL.h"
#include "Window.h"
#include "Game.h"
#include "Map.h"
#include "Surface.h"
#include "Bullet.h"
#include "PowerUp.h"


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

	if (!game->getIsPowerUpUsedUp()) {
		drawPowerUp();
	}

	drawCars();
}


void DrawService::drawCars() {
	EnemyCar* enemyCar = game->getEnemyCar();
	NeutralCar* neutralCar = game->getNeutralCar();
	
	if (!neutralCar->getIsDestroyed()) {
		drawNeutralCar();
	}
	
	if (!enemyCar->getIsDestroyed()) {
		drawEnemyCar();
	}
	
	drawPlayerCar();
}


void DrawService::drawRoadside() {
	SDL_Surface* screenSurface = sdl->screen;
	
	SDL_Rect roadsideRectangle;
	
	for (int i = 0; i < Window::WIDTH; i += sdl->grass->w) {
		for (int j = 0; j < Window::HEIGHT; j += sdl->grass->h) {
			roadsideRectangle.x = i;
			roadsideRectangle.y = j;
			roadsideRectangle.w = sdl->grass->w;
			roadsideRectangle.h = sdl->grass->h;

			SDL_BlitSurface(sdl->grass, NULL, screenSurface, &roadsideRectangle);
		}
	}
}


void DrawService::drawRoad() {
	SDL_Surface* screenSurface = sdl->screen;
	Uint32 color = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00);

	SDL_Rect roadRectangle;
	roadRectangle.x = Map::ROAD_LEFT_X;
	roadRectangle.y = Map::ROAD_TOP_Y;
	roadRectangle.w = Map::ROAD_WIDTH;
	roadRectangle.h = Map::ROAD_HEIGHT;

	SDL_FillRect(screenSurface, &roadRectangle, color);

	drawDividingLines();
}


void DrawService::drawPowerUp() {
	SDL_Surface* screenSurface = sdl->screen;
	
	SDL_Rect powerUpRectangle;
	
	powerUpRectangle.x = PowerUp::X;
	powerUpRectangle.y = PowerUp::Y;
	powerUpRectangle.w = sdl->grass->w;
	powerUpRectangle.h = sdl->grass->h;

	SDL_BlitSurface(sdl->powerUp, NULL, screenSurface, &powerUpRectangle);
}


void DrawService::drawDividingLines() {
	SDL_Surface* screenSurface = sdl->screen;
	Uint32 color = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
	double worldTime = window->getWorldTime();

	PlayerCar* playerCar = game->getPlayerCar();
	int playerCarVerticalVelocity = static_cast<int>(playerCar->getVerticalVelocity()) + 1;
	
	for (int i = -worldTime * 100 * playerCarVerticalVelocity; i < Map::ROAD_HEIGHT + worldTime * 100 * playerCarVerticalVelocity; i += Map::WHITE_LANE_HEIGHT * 2) {
		SDL_Rect whiteLineRectangle;
		whiteLineRectangle.x = Map::ROAD_MIDDLE_X - Map::WHITE_LANE_WIDTH / 2;
		//whiteLineRectangle.y = -i * playerCarVerticalVelocity + Window::HEIGHT;
		whiteLineRectangle.y = -i + Window::HEIGHT;
		whiteLineRectangle.w = Map::WHITE_LANE_WIDTH;
		whiteLineRectangle.h = Map::WHITE_LANE_HEIGHT;

		SDL_FillRect(screenSurface, &whiteLineRectangle, color);
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
	playerCarRectangle.w = Car::WIDTH;
	playerCarRectangle.h = Car::HEIGHT;
	
	SDL_BlitSurface(sdl->playerCar, NULL, screenSurface, &playerCarRectangle);

	if (playerCar->getIsShooting()) {
		drawBullets();
	}
}


void DrawService::drawPlayerCarBorder() {
	SDL_Surface* screenSurface = sdl->screen;
	Uint32 greenColor = SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00);
	Uint32 redColor = SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00);

	PlayerCar* playerCar = game->getPlayerCar();
	int x = playerCar->getX();
	int y = playerCar->getY();

	SDL_Rect playerCarBorderRectangle;
	playerCarBorderRectangle.x = x;
	playerCarBorderRectangle.y = y;
	playerCarBorderRectangle.w = Car::WIDTH;
	playerCarBorderRectangle.h = Car::HEIGHT;

	SDL_FillRect(screenSurface, &playerCarBorderRectangle, greenColor);

	// if collision with enemy car is detected, draw a red border around the player car
	if (game->isPlayerCollidingWithEnemy()) {
		SDL_FillRect(screenSurface, &playerCarBorderRectangle, redColor);
	}
}


void DrawService::drawBullets() {
	SDL_Surface* screenSurface = sdl->screen;
	Uint32 color = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);

	PlayerCar* playerCar = game->getPlayerCar();
	int x = playerCar->getX() + Car::WIDTH / 2;
	int y = playerCar->getY() - 10;
	int bulletsQuantity = playerCar->getShootingRange();

	for (int i = 0; i < bulletsQuantity; i++) {
		SDL_Rect bulletRectangle;
		bulletRectangle.x = x - Bullet::OFFSET;
		bulletRectangle.y = y - i * 20;
		bulletRectangle.w = Bullet::WIDTH;
		bulletRectangle.h = Bullet::HEIGHT;

		SDL_FillRect(screenSurface, &bulletRectangle, color);

		bulletRectangle.x = x + Bullet::OFFSET;
		SDL_FillRect(screenSurface, &bulletRectangle, color);
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
	enemyCarRectangle.w = Car::WIDTH;
	enemyCarRectangle.h = Car::HEIGHT;

	SDL_BlitSurface(sdl->enemyCar, NULL, screenSurface, &enemyCarRectangle);
}


void DrawService::drawNeutralCar() {
	SDL_Surface* screenSurface = sdl->screen;
	
	NeutralCar* neutralCar = game->getNeutralCar();
	int x = neutralCar->getX();
	int y = neutralCar->getY();

	SDL_Rect neutralCarRectangle;
	neutralCarRectangle.x = x;
	neutralCarRectangle.y = y;
	neutralCarRectangle.w = Car::WIDTH;
	neutralCarRectangle.h = Car::HEIGHT;

	SDL_BlitSurface(sdl->neutralCar, NULL, screenSurface, &neutralCarRectangle);
}


void DrawService::drawGameInformation() {
	SDL_Surface* screen = sdl->screen;
	SDL_Surface* charset = sdl->charset;

	int red = sdl->getRedColor();
	int blue = sdl->getBlueColor();
	
	int score = game->getScore();
	double worldTime = window->getWorldTime();
	double fps = window->getFps();
	
	
	char text[100];
	double scoreDoubleValue = static_cast<double>(score);

	Surface::drawRectangle(4, 4, Window::WIDTH - 8, 36, red, blue);

	if (game->getIsScoreFrozen()) {
		sprintf_s(text, "Score (frozen): %.0lf, elapsed time: %.1lf s  %.0lf frames/s", scoreDoubleValue, worldTime, fps);
	}
	else {
		sprintf_s(text, "Score: %.0lf, elapsed time: %.1lf s  %.0lf frames/s", scoreDoubleValue, worldTime, fps);
	}
	Surface::printString(screen->w / 2 - strlen(text) * 4, 10, text);

	sprintf_s(text, "Esc - exit, \030 - faster, \031 - slower, \032 - left, \033 - right");
	Surface::printString(screen->w / 2 - strlen(text) * 4, 26, text);

	drawListOfImplementedFunctionalities();
}


void DrawService::drawListOfImplementedFunctionalities() {
	SDL_Surface* screen = sdl->screen;
	SDL_Surface* charset = sdl->charset;

	int red = sdl->getRedColor();
	int blue = sdl->getBlueColor();

	char text[100];

	int widthOffset = 115;
	int heightOffset = 60;
	int lineOffset = 2;

	int const width = Window::WIDTH - widthOffset;
	int const height = Window::HEIGHT - heightOffset;

	Surface::drawRectangle(width, height, 100, 56, red, blue);

	sprintf_s(text, "Implemented:");
	Surface::printString(width, height + lineOffset, text);
	lineOffset += Window::LINE_HEIGHT;

	sprintf_s(text, " - abcdef");
	Surface::printString(width, height + lineOffset, text);
	lineOffset += Window::LINE_HEIGHT;

	sprintf_s(text, " - ij");
	Surface::printString(width, height + lineOffset, text);
}


void DrawService::drawPauseScreen() {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect blackRectangle;
	blackRectangle.x = 0;
	blackRectangle.y = 0;
	blackRectangle.w = Window::WIDTH;
	blackRectangle.h = Window::HEIGHT;
	
	Uint32 blackColor = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00);
	SDL_FillRect(screenSurface, &blackRectangle, blackColor);
	
	char text[100] = "GAME PAUSED";
	int width = Window::WIDTH / 2 - strlen(text) * 4;
	int height = Window::HEIGHT / 2;

	Surface::printString(width, height, text);

	sprintf_s(text, "Press P to continue");
	width = Window::WIDTH / 2 - strlen(text) * 4;
	height = Window::HEIGHT / 2 + Window::BIG_LINE_HEIGHT;

	Surface::printString(width, height, text);
}


void DrawService::drawGameOverScreen() {
	SDL_Surface* screenSurface = sdl->screen;

	SDL_Rect blackRectangle;
	blackRectangle.x = 0;
	blackRectangle.y = 0;
	blackRectangle.w = Window::WIDTH;
	blackRectangle.h = Window::HEIGHT;

	Uint32 blackColor = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00);
	SDL_FillRect(screenSurface, &blackRectangle, blackColor);

	char text[100] = "GAME OVER";
	int width = Window::WIDTH / 2 - strlen(text) * 4;
	int height = Window::HEIGHT / 2;

	Surface::printString(width, height, text);

	sprintf_s(text, "Press R to restart");
	width = Window::WIDTH / 2 - strlen(text) * 4;
	height = Window::HEIGHT / 2 - Window::BIG_LINE_HEIGHT;

	Surface::printString(width, height, text);
}