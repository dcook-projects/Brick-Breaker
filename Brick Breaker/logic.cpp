#include "logic.h"

constexpr int PIXEL_LEEWAY = 1;

int distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

void initializeBricks(App& app) {
	for (int row = 0; row < NUM_BRICK_ROWS; ++row) {
		for (int col = 0; col < BOARD_WIDTH / BRICK_WIDTH; ++col) {
			app.bricks[row][col].status = Brick::INTACT;
			app.bricks[row][col].collider.x = col * BRICK_WIDTH + BORDER_GAP;
			app.bricks[row][col].collider.y = row * BRICK_HEIGHT + TOP_GAP;
			app.bricks[row][col].collider.w = BRICK_WIDTH;
			app.bricks[row][col].collider.h = BRICK_HEIGHT;
		}
	}
}

bool checkCollisionWithPaddle(App& app, int* section) {
	Circle circle = app.ball.getCollider();
	SDL_Rect rect = app.paddle.getCollider();
	int halfway;

	//If the bottom of the ball is above the top of the paddle, immediately return false
	if (circle.y + circle.r < rect.y)
		return false;

	if (circle.x >= rect.x && circle.x <= rect.x + rect.w &&
		circle.y + circle.r > rect.y) {
		
		halfway = (circle.x + (circle.x - app.ball.getVelocityX())) / 2;
		if (halfway < rect.x + PADDLE_WIDTH / 3)
			*section = 1;
		else if (halfway >= rect.x + PADDLE_WIDTH / 3 && halfway <= rect.x + 2 * PADDLE_WIDTH / 3)
			*section = 2;
		else
			*section = 3;

		return true;
	}

	return false;
}

bool checkCollisionWithBricks(App& app, int* location) {
	Circle circle = app.ball.getCollider();
	SDL_Rect rect;

	//there is no collision if the ball is above or below the rows of bricks
	if (circle.y + circle.r < TOP_GAP)
		return false;
	if (circle.y - circle.r > TOP_GAP + NUM_BRICK_ROWS * BRICK_HEIGHT)
		return false;

	for (int row = 0; row < NUM_BRICK_ROWS; ++row) {
		for (int col = 0; col < BOARD_WIDTH / BRICK_WIDTH; ++col) {
			rect = app.bricks[row][col].collider;
			if (app.bricks[row][col].status == Brick::INTACT) {
				if (isBoundLeft(circle, rect)) { //left
					*location = 2;
					app.bricks[row][col].status = Brick::BROKEN;
					app.score += (NUM_BRICK_ROWS - row) * 50;
					return true;
				}
				else if (isBoundRight(circle, rect)) { //right
					*location = 2;
					app.bricks[row][col].status = Brick::BROKEN;
					app.score += (NUM_BRICK_ROWS - row) * 50;
					return true;
				}
				else if (isBoundAbove(circle, rect)) {  //above
					*location = 1;
					app.bricks[row][col].status = Brick::BROKEN;
					app.score += (NUM_BRICK_ROWS - row) * 50;
					return true;
				}
				else if (isBoundBelow(circle, rect)) { //below   
					*location = 1;
					app.bricks[row][col].status = Brick::BROKEN;
					app.score += (NUM_BRICK_ROWS - row) * 50;
					return true;
				}
			}
		}
	}
	return false;
}

void lifeLost(App& app) {
	--app.numLives;
	if (app.numLives == 0)
		gameOver(app);
	else {
		app.ball.initialize(app.paddle);
		app.paddle.initialize();
		SDL_Delay(500);
	}
}

void gameOver(App& app) {
	app.gameStatus = GAME_OVER;
}

bool isBoardEmpty(const App& app) {
	for (int row = 0; row < NUM_BRICK_ROWS; ++row)
		for (int col = 0; col < BOARD_WIDTH / BRICK_WIDTH; ++col)
			if (app.bricks[row][col].status == Brick::INTACT)
				return false;

	return true;
}

void resetGame(App& app) {
	app.gameStatus = RUNNING;
	app.numLives = 3;
	app.score = 0;
	app.ball.initialize(app.paddle);
	app.paddle.initialize();
	initializeBricks(app);
}

bool isBoundAbove(const Circle& circle, const SDL_Rect& rect) {
	return circle.y <= rect.y + (BRICK_HEIGHT / 2) && (circle.y + circle.r > rect.y) &&
		(circle.x > rect.x - PIXEL_LEEWAY) && (circle.x < rect.x + BRICK_WIDTH + PIXEL_LEEWAY);
}

bool isBoundBelow(const Circle& circle, const SDL_Rect& rect) {
	return circle.y > rect.y + (BRICK_HEIGHT / 2) && (circle.y - circle.r < rect.y + BRICK_HEIGHT) &&
		(circle.x > rect.x - PIXEL_LEEWAY) && (circle.x < rect.x + BRICK_WIDTH + PIXEL_LEEWAY);
}

bool isBoundLeft(const Circle& circle, const SDL_Rect& rect) {
	return (circle.y > rect.y + PIXEL_LEEWAY) && (circle.y < rect.y + BRICK_HEIGHT - PIXEL_LEEWAY) &&
		(circle.x + circle.r > rect.x) && (circle.x < rect.x + (BRICK_WIDTH / 2));
}

bool isBoundRight(const Circle& circle, const SDL_Rect& rect) {
	return (circle.y > rect.y + PIXEL_LEEWAY) && (circle.y < rect.y + BRICK_HEIGHT - PIXEL_LEEWAY) &&
		(circle.x - circle.r < rect.x + BRICK_WIDTH) && (circle.x > rect.x + (BRICK_WIDTH / 2));
}