#include "Paddle.h"
#include "app.h"


Paddle::Paddle() {
    mVelX = 0;
    initialize();
}

//set the initial status of the paddle
void Paddle::initialize() {
    mPosX = (BOARD_WIDTH - PADDLE_WIDTH) / 2;
    mPosY = SCREEN_HEIGHT - PADDLE_HEIGHT;

    collider.x = mPosX;
    collider.y = mPosY;
    collider.w = PADDLE_WIDTH;
    collider.h = PADDLE_HEIGHT;
}

// This sets the paddle's X velocity constant on arrow key down, and sets it to 0 on arrow key up
void Paddle::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            mVelX -= PADDLE_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += PADDLE_VEL;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            mVelX += PADDLE_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= PADDLE_VEL;
            break;
        }
    }
}

void Paddle::move()
{
    //Move the Paddle left or right
    mPosX += mVelX;

    //move the paddle's collider
    collider.x += mVelX;
    
    //If the Paddle went too far to the left or right
    if ((mPosX < BORDER_GAP - 3) || (mPosX + PADDLE_WIDTH > BOARD_WIDTH))
    {
        //Move back
        mPosX -= mVelX;
        collider.x -= mVelX;
    }
}

void Paddle::render(App& app) {
    SDL_Rect renderQuad;
    renderQuad.x = mPosX;
    renderQuad.y = mPosY;
    renderQuad.w = PADDLE_WIDTH;
    renderQuad.h = PADDLE_HEIGHT;

    app.paddleTexture.render(app, renderQuad);
}

int Paddle::getYPosition() const {
    return mPosY;
}

SDL_Rect& Paddle::getCollider() {
    return collider;
}