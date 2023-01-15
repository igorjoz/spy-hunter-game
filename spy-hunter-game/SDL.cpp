#include "SDL.h"


#include "Constants.h"
#include "Surface.h"
#include "Window.h"


#include<stdio.h>


SDL::SDL() {
	initializeSDL();
	initializeWindowAndRenderer();
}


SDL::~SDL() {
	SDL_FreeSurface(screen);
	SDL_FreeSurface(charset);

	SDL_DestroyTexture(screenTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}


void SDL::initializeSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		delete this;

		exit(1);
	}
}


void SDL::initializeWindowAndRenderer() {
	// fullscreen mode
	//int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &this->window, &this->renderer); 

	// windowed mode
	int windowAndRendererCreationCode = SDL_CreateWindowAndRenderer(Window::WIDTH, Window::HEIGHT, 0, &window, &renderer);

	if (windowAndRendererCreationCode != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		delete this;

		exit(1);
	}
}


void SDL::initializeSDLVariables() {
	initializeRendererSettings();
	
	initializeScreen();
	initializeScreenTexture();

	initializeSourceRectangle();
	initializeDestinationRectangle();
	initializeCamera();
	
	initializeColors();
}


void SDL::initializeRendererSettings() {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, Window::WIDTH, Window::HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


void SDL::initializeScreen() {
	screen = SDL_CreateRGBSurface(0, Window::WIDTH, Window::HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}


void SDL::initializeScreenTexture() {
	screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Window::WIDTH, Window::HEIGHT);
}


void SDL::initializeSourceRectangle() {
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	sourceRectangle.w = Window::WIDTH;
	sourceRectangle.h = Window::HEIGHT;
}


void SDL::initializeDestinationRectangle() {
	destinationRectangle.x = 10;
	destinationRectangle.y = 10;
	destinationRectangle.w = Window::WIDTH - 20;
	destinationRectangle.h = Window::HEIGHT - 20;
}


void SDL::initializeCamera() {
	camera.x = 0;
	camera.y = 0;
	camera.w = Window::WIDTH;
	camera.h = Window::HEIGHT;

	/*camera.x = 0;
	camera.y = -1.5 * RTILE_HEIGHT;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT * SCREEN_SIZE;*/
}


void SDL::initializeColors() {
	whiteColor = createColor(0xFF, 0xFF, 0xFF);
	blackColor = createColor(0x00, 0x00, 0x00);
	redColor = createColor(0xFF, 0x00, 0x00);
	greenColor = createColor(0x00, 0xFF, 0x00);
	blueColor = createColor(0x11, 0x11, 0xCC);
}


int SDL::createColor(int red, int green, int blue) {
	return SDL_MapRGB(screen->format, red, green, blue);
}


void SDL::renderFrame() {
	SDL_Rect rect;
	//rect.x = (int)(camera.x * 1) + 1 * Window::WIDTH;
	rect.x = (int)(camera.x * 1);
	//rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	//rect.y = (int)(camera.y * 1) + 1 * Window::HEIGHT;
	rect.y = (int)(camera.y * 1);
	//rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	printf("x: %d, y: %d\n", rect.x, rect.y);

	//if (section != NULL)
	//{
	//rect.w = sourceRectangle.w;
	rect.w = Window::WIDTH;
	rect.h = Window::HEIGHT;
		//rect.w = section->h;
		//rect.h = section->h;
		// 
	printf("w: %d, h: %d\n", rect.w, rect.h);
	//}
	/*else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}*/

	rect.w *= Window::WIDTH;
	rect.h *= Window::HEIGHT;

	SDL_RenderCopy(renderer, screenTexture, &sourceRectangle, &rect);
	
	//SDL_UpdateTexture(screenTexture, &sourceRectangle, screen->pixels, screen->pitch);
	
	SDL_UpdateTexture(screenTexture, &sourceRectangle, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, screenTexture, &sourceRectangle, &destinationRectangle);
	SDL_RenderPresent(renderer);
}


// get / set
int SDL::getWhiteColor() const {
	return whiteColor;
}


int SDL::getBlackColor() const {
	return blackColor;
}


int SDL::getRedColor() const {
	return redColor;
}


int SDL::getGreenColor() const {
	return greenColor;
}


int SDL::getBlueColor() const {
	return blueColor;
}
