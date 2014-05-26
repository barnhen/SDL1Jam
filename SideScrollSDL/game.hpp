#pragma once

#include <SDL1\SDL.h>
#include "base.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <iostream>
#include <fstream> // to read map files
#include <vector>
#include <SDL1\SDL_ttf.h>
#include "enemy.hpp"


class game:public baseclass
{
	SDL_Surface* screen, *background, *block, *bul, *ene;	
	SDL_Rect camera;
	std::vector<std::vector<int> > map;
	std::vector<bullet*> bullets;
	std::vector<enemy*> enemies;

	bool direction[2]; // for x and y coordinates
	TTF_Font* font;  
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename);
	void loadmap(const char* filename);
	void showmap();
	void handleEvents();
	bool running;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	player* player1;
	bool bound;

public:
	game();
	~game();
	void start();
	int showmenu(SDL_Surface* screen); //shows he menu
	void showMessage(const char* c);
};

