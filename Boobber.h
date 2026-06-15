#pragma once
#include <SDL3/SDL.h>
#include "GameTimer.h"
#include "Fish.h"

enum class BobberState {
    IDLE,
    FLYING,
    FLOATING,
    BITING,
    REELING,
    CAUGHT
};

class Bobber {
public:
    void init(float x, float y);
    void castTo(float tx, float ty);          // заброс к точке (мышь)
    void castRandom(float rodX, float rodY);  // случайный заброс
    void update(float dt);
    void render(SDL_Renderer* renderer);
    void resetCatch();
    void startReeling();

    bool        isCaught() const;
    Fish        getCaughtFish() const;
    BobberState getState() const { return state; }

    float getPosX() const { return rect.x + rect.w * 0.5f; }
    float getPosY() const { return rect.y + rect.h * 0.5f; }
    float getBiteProgress() const;

    // Ќат€жение лески (мини-игра)
    float getTension() const { return tension; }
    void  pullLine(float dt); // игрок нажимает SPACE
    bool  isLineBroken() const { return lineBroken; }

private:
    SDL_FRect   rect = { 0, 0, 14, 14 };
    float       homeX = 0, homeY = 0;
    float       targetX = 0, targetY = 0;
    float       flyProgress = 0.0f;
    float       startX = 0, startY = 0;

    BobberState state = BobberState::IDLE;
    GameTimer   waitTimer;
    Fish        pendingFish;

    float bobOffset = 0, bobTime = 0;
    bool  caught = false;

    // ћини-игра нат€жение
    float tension = 0.0f;   // 0..1
    bool  lineBroken = false;
    float slack = 0.0f;   // таймер "ослаблени€" лески

    void docast(float tx, float ty);
};