#include "FishingRod.h"
#include <iostream>

void FishingRod::init(float playerX, float playerY) {
    rodX = playerX + 80.0f;
    rodY = playerY - 10.0f;
    bobber.init(rodX, rodY);
}

void FishingRod::syncPosition(float playerX, float playerY) {
    // ќбновл€ем базовую позицию удочки (при движении лодки)
    // Ќо только если поплавок у лодки, чтобы не дЄргать во врем€ заброса
    rodX = playerX + 80.0f;
    rodY = playerY - 10.0f;
    BobberState bs = bobber.getState();
    if (bs == BobberState::IDLE) {
        bobber.init(rodX, rodY);
    }
}

void FishingRod::update(float dt, const InputHandler& input) {
    onSpacePressed(input);
    bobber.update(dt);
}

void FishingRod::render(SDL_Renderer* renderer) {
    BobberState bs = bobber.getState();

    // –исуем леску от кончика удилища до поплавка
    if (bs != BobberState::IDLE && bs != BobberState::CAUGHT) {
        SDL_SetRenderDrawColor(renderer, 210, 210, 210, 200);
        SDL_RenderLine(renderer,
            rodX, rodY,
            bobber.getPosX(), bobber.getPosY());
    }

    // —амо удилище Ч коричнева€ палочка
    SDL_SetRenderDrawColor(renderer, 100, 60, 20, 255);
    SDL_RenderLine(renderer, rodX - 30, rodY + 10, rodX, rodY);

    bobber.render(renderer);
}

void FishingRod::onSpacePressed(const InputHandler& input) {
    bool spaceNow = input.isKeyDown(SDL_SCANCODE_SPACE);

    if (spaceNow && !spaceWasDown) {
        BobberState bs = bobber.getState();
        if (bs == BobberState::IDLE || bs == BobberState::CAUGHT) {
            // «аброс Ч чуть вправо и вниз от кончика
            bobber.cast(rodX + 160.0f, rodY + 90.0f);
        }
        else if (bs == BobberState::BITING) {
            bobber.startReeling();
        }
        // FLOATING Ч ждЄм клЄв, ничего не делаем
    }
    spaceWasDown = spaceNow;
}

bool FishingRod::hasCatch() const { return bobber.isCaught(); }

Fish FishingRod::collectFish() {
    Fish f = bobber.getCaughtFish();
    bobber.resetCatch();
    return f;
}