#pragma once

#include "app.h"

int distanceSquared(int, int, int, int);
void initializeBricks(App& app);
bool checkCollisionWithPaddle(App& app, int* section);
bool checkCollisionWithBricks(App& app, int* location);
void lifeLost(App& app);
void gameOver(App& app);
bool isBoardEmpty(const App& app);
bool isBoundAbove(const Circle& circle, const SDL_Rect& rect);
bool isBoundBelow(const Circle& circle, const SDL_Rect& rect);
bool isBoundLeft(const Circle& circle, const SDL_Rect& rect);
bool isBoundRight(const Circle& circle, const SDL_Rect& rect);
void resetGame(App& app);