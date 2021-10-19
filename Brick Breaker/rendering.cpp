#include <sstream>
#include "rendering.h"

void renderScore(App& app);
void renderLives(App& app);
void renderGameOverStatus(App& app);

//draw the bricks on the game board
void renderBricks(App& app) {
	SDL_Rect renderQuad;
	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {

		if (app.bricks[0][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.redBrick.mTexture, NULL, &renderQuad);
		}
	}

	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {
		if (app.bricks[1][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP + BRICK_HEIGHT;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.blueBrick.mTexture, NULL, &renderQuad);
		}
	}

	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {
		if (app.bricks[2][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP + 2 * BRICK_HEIGHT;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.greenBrick.mTexture, NULL, &renderQuad);
		}
	}

	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {
		if (app.bricks[3][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP + 3 * BRICK_HEIGHT;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.orangeBrick.mTexture, NULL, &renderQuad);
		}
	}

	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {
		if (app.bricks[4][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP + 4 * BRICK_HEIGHT;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.purpleBrick.mTexture, NULL, &renderQuad);
		}
	}

	for (int i = BORDER_GAP; i < BOARD_WIDTH - BORDER_GAP; i += BRICK_WIDTH) {
		if (app.bricks[5][i / BRICK_WIDTH].status == Brick::INTACT) {
			renderQuad.x = i;
			renderQuad.y = TOP_GAP + 5 * BRICK_HEIGHT;
			renderQuad.w = BRICK_WIDTH;
			renderQuad.h = BRICK_HEIGHT;
			SDL_RenderCopy(app.renderer, app.yellowBrick.mTexture, NULL, &renderQuad);
		}
	}
}

void renderGameInfo(App& app) {
	renderScore(app);
	renderGameOverStatus(app);
	renderLives(app);
}

void renderScore(App& app) {
	std::stringstream scoreDisplay;
	scoreDisplay.str("");
	scoreDisplay << "Score: " << app.score;

	app.scoreTexture.loadFromRenderedText(app, scoreDisplay.str(), { 255, 0, 0 });
	app.scoreTexture.render(app, BOARD_WIDTH + BORDER_GAP, BORDER_GAP);
}

void renderLives(App& app) {
	std::stringstream livesDisplay;
	livesDisplay.str("");
	livesDisplay << "Lives: " << app.numLives;

	app.livesTexture.loadFromRenderedText(app, livesDisplay.str(), { 255, 0, 0 });
	app.livesTexture.render(app, BOARD_WIDTH + BORDER_GAP, SCREEN_HEIGHT - app.livesTexture.getHeight() - BORDER_GAP);
}

void renderGameOverStatus(App& app) {
	if (app.gameStatus == GAME_OVER) {
		app.gameOverTexture.loadFromRenderedText(app, "GAME OVER: Click to replay", { 255, 0, 0 });
		app.gameOverTexture.render(app, BOARD_WIDTH + BORDER_GAP, (SCREEN_HEIGHT - app.gameOverTexture.getHeight()) / 2);
	}
}