#pragma once

#include <SDL3/SDL.h>
#include "InputHandler.h"

enum class PlayerState {
    IDLE,
    CASTING,
    WAITING,
    REELING
};

class Player {
public:
    Player();
    ~Player();

    void init(float x, float y, float width, float height);
    void update(const InputHandler& input);
    void render(SDL_Renderer* renderer);
    void clean();

    PlayerState getState() const { return currentState; }
    void setState(PlayerState state) { currentState = state; }

private:
    SDL_FRect destRect;
    PlayerState currentState;
};