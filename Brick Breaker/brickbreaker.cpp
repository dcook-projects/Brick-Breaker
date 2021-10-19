/*
* David Cook
*/

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <SDL_ttf.h>
#include "app.h"
#include "dot.h"
#include "paddle.h"
#include "rendering.h"
#include "logic.h"
#include "brick.h"

bool init(App& app);
bool loadMedia(App& app);
void close(App& app);

bool init(App& app) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	app.window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (app.window == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (app.renderer == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool loadMedia(App& app) {
	if (!app.ballTexture.loadFromFile(app, "assets/dot.bmp")) {
		printf("failed to load dot texture\n");
		return false;
	}

	if (!app.paddleTexture.loadFromFile(app, "assets/paddle.png")) {
		printf("failed to load paddle texture\n");
		return false;
	}

	if (!app.borderTexture.loadFromFile(app, "assets/border.png")) {
		printf("failed to load paddle texture\n");
		return false;
	}

	if (!app.redBrick.loadFromFile(app, "assets/redbrick.png")) {
		printf("failed to load red brick texture");
		return false;
	}

	if (!app.blueBrick.loadFromFile(app, "assets/bluebrick.png")) {
		printf("failed to load blue brick texture");
		return false;
	}

	if (!app.greenBrick.loadFromFile(app, "assets/greenbrick.png")) {
		printf("failed to load green brick texture");
		return false;
	}

	if (!app.orangeBrick.loadFromFile(app, "assets/orangebrick.png")) {
		printf("failed to load orange brick texture");
		return false;
	}

	if (!app.purpleBrick.loadFromFile(app, "assets/purplebrick.png")) {
		printf("failed to load purple brick texture");
		return false;
	}

	if (!app.yellowBrick.loadFromFile(app, "assets/yellowbrick.png")) {
		printf("failed to load yellow brick texture");
		return false;
	}

	app.font = TTF_OpenFont("assets/EvilEmpire.ttf", 28);
	if (app.font == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void close(App& app) {
	//Destroy textures
	app.ballTexture.free();
	app.paddleTexture.free();
	app.redBrick.free();
	app.greenBrick.free();
	app.blueBrick.free();
	app.orangeBrick.free();
	app.purpleBrick.free();
	app.yellowBrick.free();
	app.scoreTexture.free();
	app.livesTexture.free();
	app.gameOverTexture.free();

	//Destroy Font
	TTF_CloseFont(app.font);
	app.font = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	app.window = nullptr;
	app.renderer = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit = false;
	SDL_Event e;
	App app;

	if (!init(app))
		return EXIT_FAILURE;

	if (!loadMedia(app)) {
		//getchar();
		return EXIT_FAILURE;
	}

	initializeBricks(app);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);

				//reset the game if the gfame is over and the user clicks on the board
				if (app.gameStatus == GAME_OVER && x > 0 && x < BOARD_WIDTH && y > 0 && y < SCREEN_HEIGHT) {
					resetGame(app);
				}
			}
			
			app.ball.handleEvent(e);
			app.paddle.handleEvent(e);
			
		}

		if (app.gameStatus == RUNNING) {
			app.ball.move(app);
			app.paddle.move();
		}

		//Clear screen
		SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
		SDL_RenderClear(app.renderer);

		app.borderTexture.render(app, { 0, 0, BOARD_WIDTH, SCREEN_HEIGHT });

		//draw the black background for the score section
		SDL_Rect rightSection;
		rightSection.x = BOARD_WIDTH;
		rightSection.y = 0;
		rightSection.w = SCREEN_WIDTH - BOARD_WIDTH;
		rightSection.h = SCREEN_HEIGHT;
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(app.renderer, &rightSection);

		if (app.gameStatus == RUNNING) {
			app.ball.render(app);
			app.paddle.render(app);
		}

		renderBricks(app);
		renderGameInfo(app);

		//Update screen
		SDL_RenderPresent(app.renderer);
	}

	close(app);
	return 0;
}