#pragma once
#include <SDL1\SDL.h>
#include<vector>
#include "base.hpp"

class enemy:public baseclass
{
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface* image;
	bool ground;
	SDL_Rect clips[2];
	double frame;

	public:
		enemy(SDL_Surface* img, int x, int y, int xVel, int yVel);
		void move(std::vector<std::vector<int> >& map);
		void show(SDL_Surface* screen);
		SDL_Rect* getRect();
};

