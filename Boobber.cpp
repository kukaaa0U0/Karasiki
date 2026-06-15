#include "Boobber.h"
#include <cmath>
#include <iostream>

void Bobber::init(float x, float y) {
    homeX = x; homeY = y;
    rect.x = x; rect.y = y;
    state = BobberState::IDLE;
    caught = false;
}

void Bobber::cast(float tx, float ty) {
    targetX = tx;
    targetY = ty;
    startX = homeX;
    startY = homeY;
    flyProgress = 0.0f;

    pendingFish = Fish::random();
    caught = false;
    state = BobberState::FLYING;

    std::cout << "Cast! Fish: " << pendingFish.name
        << " delay=" << pendingFish.biteDelay << "s" << std::endl;
}

void Bobber::update(float dt) {
    switch (state) {

    case BobberState::FLYING: {
        // ѕараболический полЄт к цели
        flyProgress += dt * 1.8f;   // скорость полЄта
        if (flyProgress >= 1.0f) {
            flyProgress = 1.0f;
            rect.x = targetX;
            rect.y = targetY;
            waitTimer.start();
            state = BobberState::FLOATING;
        }
        else {
            float t = flyProgress;
            // Ћинейна€ интерпол€ци€ + парабола по Y дл€ дуги
            rect.x = startX + (targetX - startX) * t;
            float baseY = startY + (targetY - startY) * t;
            float arc = -80.0f * t * (1.0f - t);   // дуга вверх
            rect.y = baseY + arc;
        }
        break;
    }

    case BobberState::FLOATING:
        // ѕокачивание
        bobTime += dt;
        bobOffset = std::sin(bobTime * 2.5f) * 3.0f;
        rect.y = targetY + bobOffset;

        if (waitTimer.hasElapsed(pendingFish.biteDelay)) {
            state = BobberState::BITING;
            std::cout << "Bite! Press SPACE!" << std::endl;
        }
        break;

    case BobberState::BITING:
        // –езкое дЄрганье
        bobTime += dt * 8.0f;
        bobOffset = std::sin(bobTime) * 10.0f;
        rect.y = targetY + bobOffset;

        // ≈сли не успел за 3 секунды Ч рыба ушла
        if (waitTimer.hasElapsed(pendingFish.biteDelay + 3.0f)) {
            std::cout << "Fish got away!" << std::endl;
            state = BobberState::IDLE;
            rect.x = homeX; rect.y = homeY;
        }
        break;

    case BobberState::REELING: {
        // ѕоплавок едет к лодке
        float dx = homeX - rect.x;
        float dy = homeY - rect.y;
        float speed = 200.0f * dt;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist < speed || dist < 3.0f) {
            rect.x = homeX; rect.y = homeY;
            caught = true;
            state = BobberState::CAUGHT;
            std::cout << "Caught: " << pendingFish.toString() << std::endl;
        }
        else {
            rect.x += (dx / dist) * speed;
            rect.y += (dy / dist) * speed;
        }
        break;
    }

    case BobberState::CAUGHT:
    case BobberState::IDLE:
    default:
        break;
    }
}

void Bobber::render(SDL_Renderer* renderer) {
    if (state == BobberState::IDLE || state == BobberState::CAUGHT) return;

    // ÷вет зависит от состо€ни€
    if (state == BobberState::BITING) {
        SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255);   // красный Ч клюЄт!
    }
    else if (state == BobberState::FLYING) {
        SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);   // оранжевый Ч летит
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 210, 0, 255);   // жЄлтый Ч плывЄт
    }

    SDL_RenderFillRect(renderer, &rect);

    // Ѕела€ точка сверху поплавка
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_FRect dot = { rect.x + 3, rect.y + 2, 4, 4 };
    SDL_RenderFillRect(renderer, &dot);
}

void Bobber::startReeling() {
    if (state == BobberState::BITING) {
        state = BobberState::REELING;
        std::cout << "Reeling!" << std::endl;
    }
}

void Bobber::resetCatch() {
    caught = false;
    state = BobberState::IDLE;
    rect.x = homeX; rect.y = homeY;
}

bool Bobber::isCaught() const { return caught; }
Fish Bobber::getCaughtFish() const { return pendingFish; }

float Bobber::getBiteProgress() const {
    if (state != BobberState::FLOATING) return 0.0f;
    float elapsed = waitTimer.getElapsed();
    return elapsed / pendingFish.biteDelay;
}