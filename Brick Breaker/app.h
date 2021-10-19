#pragma once

#include <SDL_ttf.h>
#include "ltexture.h"
#include "brick.h"
#include "dot.h"
#include "paddle.h"

constexpr int SCREEN_WIDTH = 1100;
constexpr int SCREEN_HEIGHT = 700;
constexpr int BOARD_WIDTH = 760;

//The dimensions of the dot
constexpr int DOT_WIDTH = 14;
constexpr int DOT_HEIGHT = 14;

//Velocity increment and maximum axis velocity of the dot
constexpr int DOT_VEL = 8;
constexpr int MAX_DOT_VEL = 17;

//The dimensions of the paddle
constexpr int PADDLE_WIDTH = 75;
constexpr int PADDLE_HEIGHT = 20;

constexpr int BRICK_WIDTH = 50;
constexpr int BRICK_HEIGHT = 20;

//Maximum paddle velocity
constexpr int PADDLE_VEL = 10;

//brick positioning constants
constexpr int TOP_GAP = 100;
constexpr int BORDER_GAP = 5;
constexpr int NUM_BRICK_ROWS = 6;

enum Game_Status {
	RUNNING,
	GAME_OVER
};

struct App {
	//building blocks of the game
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//font used to display info
	TTF_Font* font = nullptr;

	//used to determine whether the game is currently running or not
	Game_Status gameStatus = RUNNING;

	//textures used in the game
	LTexture ballTexture;
	LTexture paddleTexture;
	LTexture borderTexture;
	LTexture redBrick;
	LTexture blueBrick;
	LTexture greenBrick;
	LTexture orangeBrick;
	LTexture purpleBrick;
	LTexture yellowBrick;

	//text textures used in the game
	LTexture scoreTexture;
	LTexture livesTexture;
	LTexture gameOverTexture;

	//logical representation of the bricks on the board
	Brick bricks[NUM_BRICK_ROWS][BOARD_WIDTH / BRICK_WIDTH];

	Dot ball;
	Paddle paddle;

	//player info
	unsigned int score = 0;
	int numLives = 3;
};