#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "InputHandler.h"
#include "FishingRod.h"

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
    void update(float dt, const InputHandler& input);
    void render(SDL_Renderer* renderer);
    void clean();

    PlayerState getState() const { return currentState; }
    void setState(PlayerState state) { currentState = state; }

    const std::vector<std::string>& getCatch() const { return caughtFish; }
    int getTotalScore() const { return totalScore; }
    BobberState getBobberState() const { return rod.getBobberState(); }
    float getBiteProgress() const { return rod.getBiteProgress(); }

    float getX() const { return destRect.x; }
    float getY() const { return destRect.y; }

private:
    SDL_FRect destRect = { 0, 0, 0, 0 };
    PlayerState currentState = PlayerState::IDLE;

    FishingRod rod;
    std::vector<std::string> caughtFish;
    int totalScore = 0;

    static constexpr float WATER_LEFT = 20.0f;
    static constexpr float WATER_RIGHT = 700.0f;
    static constexpr float MOVE_SPEED = 150.0f;
};