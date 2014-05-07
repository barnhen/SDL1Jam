#include <SDL1\SDL.h>
#include <iostream>

SDL_Surface *screen;

int main (int argc, char *argv[]) //main params are required for SDL 1.2
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout<<"failed to load everything"<<std::endl;
		return 1; //false
	}

	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
	if (screen == nullptr) // NULL's ugly cousin
	{
		std::cout<<"screen hasn't loaded"<<std::endl;
		return 1;
	}

	while (1)
	{
		SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,150));
		if (SDL_Flip(screen) == -1)
		{
			std::cout<<"Flip went wrong"<<std::endl; 
			return 1;
		}
	}
	SDL_Quit();
	return 0;
}