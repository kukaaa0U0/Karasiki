#pragma once
#include <SDL3/SDL.h>
#include "Boobber.h"
#include "InputHandler.h"

class FishingRod {
public:
    void init(float playerX, float playerY);
    void update(float dt, const InputHandler& input);
    void render(SDL_Renderer* renderer);
    void syncPosition(float playerX, float playerY);  // обновляем позицию при движении лодки

    bool hasCatch() const;
    Fish collectFish();

    BobberState getBobberState() const { return bobber.getState(); }
    float getBiteProgress() const { return bobber.getBiteProgress(); }

private:
    Bobber bobber;
    float rodX = 0, rodY = 0;

    bool spaceWasDown = false;
    void onSpacePressed(const InputHandler& input);
};