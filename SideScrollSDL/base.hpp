#pragma once
#include <SDL1\SDL.h>

class baseclass
{
protected:
	bool collision(SDL_Rect* rec1, SDL_Rect* rec2);
public:
	static SDL_Rect coord;//coord variable, store the absolute coordinate of the screen, so if I go a 1000px it will be a 1000px
    //actual memory will be reserved in the game.cpp
	
	static const int TILE_SIZE=50;

};