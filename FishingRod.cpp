#include "FishingRod.h"
#include <iostream>
#include "Boobber.h"

void FishingRod::init(float playerX, float playerY) {
    rodX = playerX + 80.0f;   // конец удочки правее лодки
    rodY = playerY - 10.0f;
    bobber.init(rodX, rodY);
}

void FishingRod::update(float dt, const InputHandler& input) {
    onSpacePressed(input);
    bobber.update(dt);
}

void FishingRod::render(SDL_Renderer* renderer) {
    // Ћеска от удилища до поплавка
    BobberState bs = bobber.getState();
    if (bs != BobberState::IDLE) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 180);
        // SDL_RenderLine Ч рисуем леску (тонка€ лини€)
        SDL_RenderLine(renderer, rodX, rodY,
            bobber.getState() != BobberState::IDLE ? rodX + 80 : rodX,
            rodY + 60);
    }
    bobber.render(renderer);
}

void FishingRod::onSpacePressed(const InputHandler& input) {
    bool spaceNow = input.isKeyDown(SDL_SCANCODE_SPACE);

    if (spaceNow && !spaceWasDown) {   // именно нажатие, не удержание
        BobberState bs = bobber.getState();
        if (bs == BobberState::IDLE) {
            // «аброс Ч фиксированна€ точка правее лодки
            bobber.cast(rodX + 150.0f, rodY + 80.0f);
        }
        else if (bs == BobberState::BITING) {
            bobber.startReeling();
        }
        // ѕри FLOATING Ч ничего, ждЄм клЄв
    }
    spaceWasDown = spaceNow;
}

bool FishingRod::hasCatch() const { return bobber.isCaught(); }
Fish FishingRod::collectFish() {
    Fish f = bobber.getCaughtFish();
    bobber.resetCatch();   // сбрасываем флаг после того как забрали
    return f;
}