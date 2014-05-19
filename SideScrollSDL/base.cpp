#include "base.hpp"

bool baseclass::collision (SDL_Rect* rec1, SDL_Rect* rec2)
{
	if (rec1->y >= rec2->y + rec2->h)
	{
		return false;
	}

	if (rec1->x >= rec2->x + rec2->w)
	{
		return false;
	}
	
	if (rec1->y + rec1->h <= rec2->y)
	{
		return false;
	}

	if (rec1->x + rec1->w <= rec2->x)
	{
		return false;
	}
	return true;
}