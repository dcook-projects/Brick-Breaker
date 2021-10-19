#pragma once

#include <SDL.h>

struct Brick
{
	//BRICK_STATUS status;
	enum {
			BROKEN,
			INTACT
	} status;
	SDL_Rect collider;	
};