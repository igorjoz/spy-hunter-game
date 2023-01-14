#include "Surface.h"


#include "SDL.h"
#include "Window.h"
#include "Game.h"


SDL* Surface::sdl = nullptr;
Window* Surface::window = nullptr;
Game* Surface::game = nullptr;


void Surface::initialize(SDL* sdlObject, Window* windowObject, Game* gameObject) {
	sdl = sdlObject;
	window = windowObject;
	game = gameObject;
}


// print text on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void Surface::printString(int x, int y, const char* text) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		
		SDL_BlitSurface(sdl->charset, &s, sdl->screen, &d);
		
		x += 8;
		text++;
	}
};


// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Surface::drawSurface(SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	
	SDL_BlitSurface(sprite, NULL, sdl->screen, &dest);
};


// draw a single pixel
void Surface::drawPixel(int x, int y, Uint32 color) {
	SDL_PixelFormat* screenFormat = sdl->screen->format;

	int bpp = screenFormat->BytesPerPixel;
	Uint8* p = (Uint8*)sdl->screen->pixels + y * sdl->screen->pitch + x * bpp;
	*(Uint32*)p = color;
};


// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Surface::drawLine(int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		Surface::drawPixel(x, y, color);
		x += dx;
		y += dy;
	};
};


// draw a rectangle of size l by k
void Surface::drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	Surface::drawLine(x, y, k, 0, 1, outlineColor);
	Surface::drawLine(x + l - 1, y, k, 0, 1, outlineColor);
	Surface::drawLine(x, y, l, 1, 0, outlineColor);
	Surface::drawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++) {
		Surface::drawLine(x + 1, i, l - 2, 1, 0, fillColor);
	}
};
