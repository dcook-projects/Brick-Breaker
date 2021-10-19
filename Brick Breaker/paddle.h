#pragma once

#include <SDL.h>

struct App;

class Paddle
{
public:
	Paddle();

	void handleEvent(SDL_Event& e);
	void move();
	void render(App& app);
	void initialize();
	int getYPosition() const;
	SDL_Rect& getCollider();

	int getVelocityX() {
		return mVelX;
	}

private:
	SDL_Rect collider;
	int mPosX, mPosY;
	int mVelX;
};