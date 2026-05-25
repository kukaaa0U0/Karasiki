#pragma once
#include <SDL3/SDL.h>
#include "Bobber.h"
#include "InputHandler.h"

class FishingRod {
public:
    void init(float playerX, float playerY);
    void update(float dt, const InputHandler& input);
    void render(SDL_Renderer* renderer);

    bool hasCatch() const;
    Fish collectFish();   // забираем пойманную рыбу

private:
    Bobber bobber;
    float rodX = 0, rodY = 0;   // конец удилища (откуда летит леска)

    bool spaceWasDown = false;   // чтобы не считать удержание как спам
    void onSpacePressed(const InputHandler& input);
};