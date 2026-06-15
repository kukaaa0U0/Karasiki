#pragma once
#include <SDL3/SDL.h>
#include "Boobber.h"
#include "InputHandler.h"

class FishingRod {
public:
    void init(float playerX, float playerY);
    void update(float dt, const InputHandler& input, float mouseX, float mouseY, bool mouseClicked);
    void render(SDL_Renderer* renderer);
    void syncPosition(float playerX, float playerY);

    bool hasCatch()      const;
    bool hadLineBroken() const { return rodLineBroke; }
    void clearLineBroke() { rodLineBroke = false; }
    Fish collectFish();

    BobberState getBobberState()  const { return bobber.getState(); }
    float       getBiteProgress() const { return bobber.getBiteProgress(); }
    float       getTension()      const { return bobber.getTension(); }

    float rodX = 0, rodY = 0;

private:
    Bobber bobber;
    bool   spaceWasDown = false;
    bool   mouseWasClick = false;
    bool   rodLineBroke = false;

    void handleInput(const InputHandler& input, float mouseX, float mouseY, bool mouseClicked);
};