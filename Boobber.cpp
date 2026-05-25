#include "Boobber.h"
#include <cmath>
#include <iostream>

void Bobber::init(float x, float y) {
    homeX = x; homeY = y;
    rect.x = x; rect.y = y;
    state = BobberState::IDLE;
}

void Bobber::cast(float targetX, float targetY) {
    this->targetX = targetX;
    this->targetY = targetY;
    rect.x = targetX;
    rect.y = targetY;

    // Генерируем рыбу и запускаем таймер ожидания клёва
    pendingFish = Fish::random();
    waitTimer.start();
    caught = false;
    state = BobberState::FLOATING;

    std::cout << "Заброс! Ждём: " << pendingFish.name << " через "
        << pendingFish.biteDelay << " сек." << std::endl;
}

void Bobber::update(float dt) {
    switch (state) {
    case BobberState::FLOATING:
        // Покачивание на воде
        bobTime += dt;
        bobOffset = std::sin(bobTime * 3.0f) * 3.0f;
        rect.y = targetY + bobOffset;

        // Проверяем, пора ли клевать
        if (waitTimer.hasElapsed(pendingFish.biteDelay)) {
            state = BobberState::BITING;
            std::cout << "Клюёт! Жми пробел!" << std::endl;
        }
        break;

    case BobberState::BITING:
        // Резкое дёрганье поплавка
        bobTime += dt * 6.0f;
        bobOffset = std::sin(bobTime) * 8.0f;
        rect.y = targetY + bobOffset;
        break;

    case BobberState::REELING:
        // Поплавок едет обратно к лодке
        rect.x += (homeX - rect.x) * 0.1f;
        rect.y += (homeY - rect.y) * 0.1f;

        if (std::abs(rect.x - homeX) < 2.0f) {
            caught = true;
            state = BobberState::IDLE;
            std::cout << "Поймал: " << pendingFish.toString() << std::endl;
        }
        break;

    default:
        break;
    }
}

void Bobber::render(SDL_Renderer* renderer) {
    if (state == BobberState::IDLE) return;

    // Цвет поплавка зависит от состояния
    if (state == BobberState::BITING) {
        SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);   // красный — клюёт!
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);   // жёлтый — плывёт
    }
    SDL_RenderFillRect(renderer, &rect);
}

void Bobber::startReeling() {
    if (state == BobberState::BITING) {
        state = BobberState::REELING;
    }
}

bool Bobber::isCaught() const { return caught; }
Fish Bobber::getCaughtFish() const { return pendingFish; }