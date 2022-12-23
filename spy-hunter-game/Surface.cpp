#include "Surface.h"


// print text on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void Surface::printString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
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
		
		SDL_BlitSurface(charset, &s, screen, &d);
		
		x += 8;
		text++;
	};
};


// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Surface::drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// draw a single pixel
void Surface::drawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Surface::drawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		Surface::drawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// draw a rectangle of size l by k
void Surface::drawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	Surface::drawLine(screen, x, y, k, 0, 1, outlineColor);
	Surface::drawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	Surface::drawLine(screen, x, y, l, 1, 0, outlineColor);
	Surface::drawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		Surface::drawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};


void Surface::printProjectAndTimeInformation(char* text, SDL_Surface* screen, SDL_Surface* charset, int red, int blue, double worldTime, double fps) {
	Surface::drawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, blue);
	sprintf(text, "template for the second project, elapsed time = %.1lf s  %.0lf frames / s", worldTime, fps);
	Surface::printString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	sprintf(text, "Esc - exit, \030 - faster, \031 - slower");
	Surface::printString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
}
