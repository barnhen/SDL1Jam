#pragma once

#include <SDL1\SDL.h>
#include "base.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <iostream>
#include <fstream> // to read map files
#include <vector>


class game:public baseclass
{
	SDL_Surface* screen, *background, *block, *bul;
	SDL_Rect camera;
	std::vector<std::vector<int> > map;
	std::vector<bullet*> bullets;
	bool direction[2]; // for x and y coordinates
	SDL_Surface* load_image(const char* filename);
	void loadmap(const char* filename);
	void showmap();
	void handleEvents();
	bool running;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	player* player1;

public:
	game();
	~game();
	void start();
};

