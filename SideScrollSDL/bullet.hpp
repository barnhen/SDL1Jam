#pragma once
#include <SDL1\SDL.h>
#include <iostream>

class bullet
{
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface* image;
	public:
		bullet(SDL_Surface* img, int x, int y, int xVel, int yVel);
		void move();
		void show(SDL_Surface* screen);
		SDL_Rect* getRect();
		//bullet(void);
		//~bullet(void);
};

