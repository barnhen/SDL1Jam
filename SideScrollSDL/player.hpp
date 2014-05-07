#pragma once

#include <SDL1\SDL.h>
#include <iostream>
#include <vector>
#include "base.hpp"

class player:baseclass
{
	SDL_Rect box;
	SDL_Surface* image;
	int xvel, yvel;
	SDL_Rect clips[4];
	bool ground;
public:
	player(SDL_Surface* img);
	~player(void);
	SDL_Rect* getRect();
	void setXvel(int vel);
	int getXvel();
	void move(const std::vector<std::vector<int> >& map);
	void show (SDL_Surface* screen);
};

