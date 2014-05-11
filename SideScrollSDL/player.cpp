#include "player.hpp"


player::player(SDL_Surface* img)
{
	image = img;
	box.x = 0;
	box.y = 0;
	box.w = 50;
	box.h = 100;

	xvel = 0;
	yvel = 0;

	//4 is the clips size
	for (int i = 0; i < 4; i++)
	{
		clips[i].x = i * 50;
		clips[i].y = 0;
		clips[i].w = clips[i].h = 50;
	}
	ground = false;
	jump = false;
	direction = 'r';
}

void player::setJump()
{
	if (ground && !jump)
	{
		jump = true;
		ground = false;
		yvel = -17; //velocity from jumping from ground to mid-air until reaches 0 and it increase from 0 to more until reaches the ground
		box.y -= 5;
	}
	
}

player::~player(void)
{
	SDL_FreeSurface(image);
}

SDL_Rect* player::getRect()
{
	return &box;
}

int player::getXvel()
{
	return xvel;
}

void player::setXvel(int vel)
{
	xvel = vel;
}

void player::show(SDL_Surface* screen)
{
	SDL_BlitSurface(image, &clips[0], screen, &box);
}

void player::move(const std::vector<std::vector<int> >& map)
{
	int start = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
	
	if (start < 0)
	{
		start=0;
	}
	if (end > map[0].size())
	{
		end = map[0].size();
	}
	bool nc = false; // non collision

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = start; j < end; j++)
		{
			if(map[i][j] == 0)
				continue;
			SDL_Rect destrect =  { j * 50 - baseclass::coord.x,i * 50, 50, 50 };
			if (collision(&box, &destrect))
			{
				nc = 1;
				if(destrect.y >= box.y + box.h - 11)
				{
					ground = true;
					yvel= 0 ;
				}
				else if (destrect.y + destrect.h <= box.y + 11)
				{
					box.x++;
					yvel = 5; // this will be gravity
				}
				if (box.x + box.w >= destrect.x - 5 && 
					box.y + box.h >= destrect.y + 6 && 
					box.x + box.w <= destrect.x + 20)
				{
					xvel = 0;
					box.x--;

				}
				else if (box.x <= destrect.x + destrect.w &&
						 box.y + box.h >= destrect.y + 6)
				{
					xvel = 0;
					box.x++;
				}
			}
		}
	}
	if (!nc && !jump) // not colliding nor jumping
	{
		yvel=5;
	}
	if (jump && yvel < 5)
	{
		yvel++;
	}
	else
	{
		jump = false;
	}
	
	box.x += xvel;
	box.y += yvel;
}