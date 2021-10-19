#include <time.h>
#include "dot.h"
#include "app.h"
#include "logic.h"

Dot::Dot() {
    srand(time(0));
    
    
    collider.r = DOT_WIDTH / 2;
    mVelX = 0;
    mVelY = 0;
    mPosX = (BOARD_WIDTH - DOT_WIDTH) / 2;
    mPosY = SCREEN_HEIGHT - PADDLE_HEIGHT - DOT_HEIGHT;
    status = STOPPED;
    shiftCollider();
}

//set the initial status of the dot
void Dot::initialize(Paddle& paddle) {
    mVelX = paddle.getVelocityX();
    mVelY = 0;
    mPosX = ((BOARD_WIDTH - DOT_WIDTH) / 2) + mVelX;
    mPosY = SCREEN_HEIGHT - PADDLE_HEIGHT - DOT_HEIGHT;
    status = STOPPED;
}

// This sets the dot's velocity constant on arrow key down, and sets it to 0 on arrow key up
void Dot::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {   
        if (status == STOPPED)
        {
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                mVelY -= DOT_VEL;
                mVelX += DOT_VEL;

                if (mVelX > DOT_VEL)
                    mVelX = DOT_VEL;

                status = MOVING;
            }
            else if (e.key.keysym.sym == SDLK_LEFT)
                mVelX -= PADDLE_VEL;
            else if (e.key.keysym.sym == SDLK_RIGHT)
                mVelX += PADDLE_VEL;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (status == STOPPED)
        {
            if (e.key.keysym.sym == SDLK_LEFT)           
                mVelX += PADDLE_VEL;
                //mVelX = 0;            
            else if (e.key.keysym.sym == SDLK_RIGHT)
                mVelX -= PADDLE_VEL;
                //mVelX = 0;
        }
    }
}

void Dot::move(App& app)
{
    //Move the dot left or right
    mPosX += mVelX;
    shiftCollider();
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > BOARD_WIDTH + BORDER_GAP)) {
        mPosX -= mVelX;
        mVelX = -mVelX;
        shiftCollider();
    }

    //Move the dot up or down
    mPosY += mVelY;
    shiftCollider();
    if (mPosY < BORDER_GAP) {
        mPosY -= mVelY;
        mVelY = -mVelY;
        shiftCollider();
    }

    //check that the ball doesn't move when attached to the paddle and the paddle is pushing against a wall
    if (status == STOPPED && mPosX < (PADDLE_WIDTH - DOT_WIDTH) / 2 && mVelX < 0) {
        mPosX -= mVelX;
        shiftCollider();
    }
    else if (status == STOPPED && mPosX > BOARD_WIDTH - ((PADDLE_WIDTH - DOT_WIDTH) / 2) - DOT_WIDTH && mVelX > 0) {
        mPosX -= mVelX;
        shiftCollider();
    }

    //ball has hit the bottom of the window
    if (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) {
        status = STOPPED;
        lifeLost(app);
        return;
    }

    int section = 0;
    //If there is a collision with the paddle, change the x velocity of the ball slightly, randomly
    if (checkCollisionWithPaddle(app, &section)) {
        if (section == 1)
            mVelX -= 5;
        else if (section == 3)
            mVelX += 5;

        if (mVelX < -MAX_DOT_VEL)
            mVelX = -MAX_DOT_VEL;

        if (mVelX > MAX_DOT_VEL)
            mVelX = MAX_DOT_VEL;

        mPosY -= mVelY;
        mVelY = -mVelY;
        shiftCollider();
    }

    section = 0;
    if (checkCollisionWithBricks(app, &section)) {
        //move the ball back one frame if there was a collision
        mPosX -= mVelX;
        mPosY -= mVelY;

        if (section == 1) 
            mVelY = -mVelY;
        else if (section == 2)
            mVelX = -mVelX;

        if (isBoardEmpty(app))
            gameOver(app);
    }
}

void Dot::render(App &app) {
    SDL_Rect renderQuad;
    renderQuad.x = mPosX;
    renderQuad.y = mPosY;
    renderQuad.w = DOT_WIDTH;
    renderQuad.h = DOT_HEIGHT;

    app.ballTexture.render(app, renderQuad);
}

Circle& Dot::getCollider() {
    return collider;
}

void Dot::shiftCollider() {
    collider.x = mPosX + DOT_WIDTH / 2;
    collider.y = mPosY + DOT_HEIGHT / 2;
}