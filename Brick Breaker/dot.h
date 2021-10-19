#pragma once

#include <SDL.h>
#include "paddle.h"

struct App;

struct Circle {
	int x, y;  //these x and y coordinates refer to the center of the circle
	int r;
};

class Dot
{
public:
	Dot();

	void handleEvent(SDL_Event& e);
	void move(App& app);
	void render(App &app);
	void initialize(Paddle& paddle);
	Circle& getCollider();
	
	int getVelocityX() {
		return mVelX;
	}

	enum {
		STOPPED,
		MOVING
	} status;

private:
	void shiftCollider();

	int mPosX, mPosY;  
	int mVelX, mVelY;
	Circle collider;
};