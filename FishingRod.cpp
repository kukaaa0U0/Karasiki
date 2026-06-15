#include "FishingRod.h"
#include <iostream>

void FishingRod::init(float playerX, float playerY) {
    rodX = playerX + 80.0f;
    rodY = playerY - 10.0f;
    bobber.init(rodX, rodY);
}

void FishingRod::syncPosition(float playerX, float playerY) {
    rodX = playerX + 80.0f;
    rodY = playerY - 10.0f;
    if (bobber.getState() == BobberState::IDLE) {
        bobber.init(rodX, rodY);
    }
}

void FishingRod::update(float dt, const InputHandler& input,
    float mouseX, float mouseY, bool mouseClicked) {
    handleInput(input, mouseX, mouseY, mouseClicked);
    bobber.update(dt);
    if (bobber.isLineBroken()) rodLineBroke = true;
}

void FishingRod::handleInput(const InputHandler& input,
    float mouseX, float mouseY, bool mouseClicked) {
    bool spaceNow = input.isKeyDown(SDL_SCANCODE_SPACE);
    BobberState bs = bobber.getState();

    // Ќажатие SPACE
    if (spaceNow && !spaceWasDown) {
        if (bs == BobberState::IDLE || bs == BobberState::CAUGHT) {
            bobber.castRandom(rodX, rodY);
        }
        else if (bs == BobberState::BITING) {
            bobber.startReeling();
        }
    }

    // ”держание SPACE во врем€ вытаскивани€ Ч ослабл€ем нат€жение
    if (spaceNow && bs == BobberState::REELING) {
        bobber.pullLine(1.0f / 60.0f);
    }
    spaceWasDown = spaceNow;

    //  лик мышью Ч заброс в точку
    if (mouseClicked && !mouseWasClick) {
        if (bs == BobberState::IDLE || bs == BobberState::CAUGHT) {
            bobber.castTo(mouseX, mouseY);
        }
        else if (bs == BobberState::BITING) {
            bobber.startReeling();
        }
    }
    mouseWasClick = mouseClicked;
}

void FishingRod::render(SDL_Renderer* renderer) {
    BobberState bs = bobber.getState();

    // Ћеска
    if (bs != BobberState::IDLE && bs != BobberState::CAUGHT) {
        // ÷вет лески по нат€жению
        if (bs == BobberState::REELING) {
            float t = bobber.getTension();
            Uint8 rv = (Uint8)(180 + t * 75);
            Uint8 gv = (Uint8)(180 - t * 150);
            SDL_SetRenderDrawColor(renderer, rv, gv, 80, 220);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 160);
        }
        SDL_RenderLine(renderer, (int)rodX, (int)rodY,
            (int)bobber.getPosX(), (int)bobber.getPosY());
    }

    // ”дилище
    SDL_SetRenderDrawColor(renderer, 120, 75, 25, 255);
    SDL_RenderLine(renderer, (int)(rodX - 35), (int)(rodY + 12), (int)rodX, (int)rodY);
    // —ветла€ полоска
    SDL_SetRenderDrawColor(renderer, 180, 130, 60, 180);
    SDL_RenderLine(renderer, (int)(rodX - 33), (int)(rodY + 10), (int)(rodX - 2), (int)(rodY + 2));

    bobber.render(renderer);
}

bool FishingRod::hasCatch() const { return bobber.isCaught(); }

Fish FishingRod::collectFish() {
    Fish f = bobber.getCaughtFish();
    bobber.resetCatch();
    return f;
}