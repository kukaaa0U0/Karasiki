#include "Boobber.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

static const float WATER_Y_CONST = 310.0f;

void Bobber::init(float x, float y) {
    homeX = x; homeY = y;
    rect.x = x; rect.y = y;
    state = BobberState::IDLE;
    caught = false;
    tension = 0.0f;
    lineBroken = false;
}

void Bobber::docast(float tx, float ty) {
    targetX = tx;
    targetY = ty;
    startX = homeX;
    startY = homeY;
    flyProgress = 0.0f;
    pendingFish = Fish::random();
    caught = false;
    lineBroken = false;
    tension = 0.0f;
    state = BobberState::FLYING;
    std::cout << "Cast! Fish: " << pendingFish.name << " delay=" << pendingFish.biteDelay << "s\n";
}

void Bobber::castTo(float tx, float ty) {
    // Ограничиваем: только в воду
    if (ty < WATER_Y_CONST) ty = WATER_Y_CONST + 10;
    docast(tx, ty);
}

void Bobber::castRandom(float rodX, float rodY) {
    float tx = rodX + 80.0f + (rand() % 180) - 60.0f;
    float ty = WATER_Y_CONST + 20 + rand() % 140;
    docast(tx, ty);
}

void Bobber::update(float dt) {
    switch (state) {
    case BobberState::FLYING: {
        flyProgress += dt * 1.6f;
        if (flyProgress >= 1.0f) {
            flyProgress = 1.0f;
            rect.x = targetX; rect.y = targetY;
            waitTimer.start();
            state = BobberState::FLOATING;
        }
        else {
            float t = flyProgress;
            rect.x = startX + (targetX - startX) * t;
            float baseY = startY + (targetY - startY) * t;
            float arc = -100.0f * t * (1.0f - t);
            rect.y = baseY + arc;
        }
        break;
    }
    case BobberState::FLOATING:
        bobTime += dt;
        bobOffset = std::sin(bobTime * 2.2f) * 3.0f;
        rect.y = targetY + bobOffset;
        if (waitTimer.hasElapsed(pendingFish.biteDelay)) {
            state = BobberState::BITING;
            waitTimer.start(); // reset for 3s window
            std::cout << "Bite!\n";
        }
        break;

    case BobberState::BITING:
        bobTime += dt * 9.0f;
        bobOffset = std::sin(bobTime) * 11.0f;
        rect.y = targetY + bobOffset;
        if (waitTimer.hasElapsed(3.0f)) {
            std::cout << "Fish got away!\n";
            state = BobberState::IDLE;
            rect.x = homeX; rect.y = homeY;
        }
        break;

    case BobberState::REELING: {
        // Натяжение само растёт (рыба тянет)
        tension += dt * (0.08f + pendingFish.weight * 0.015f);
        // Ослабление если нет нажатий
        slack += dt;
        if (slack > 0.3f) {
            tension -= dt * 0.25f;
        }
        if (tension < 0) tension = 0;
        if (tension > 1.0f) {
            lineBroken = true;
            tension = 0;
            state = BobberState::IDLE;
            rect.x = homeX; rect.y = homeY;
            std::cout << "Line broke!\n";
            break;
        }

        // Движем поплавок к лодке
        float dx = homeX - rect.x;
        float dy = homeY - rect.y;
        float speed = (80.0f + (1.0f - tension) * 80.0f) * dt;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist < speed || dist < 5.0f) {
            rect.x = homeX; rect.y = homeY;
            caught = true;
            state = BobberState::CAUGHT;
            std::cout << "Caught: " << pendingFish.toString() << "\n";
        }
        else {
            rect.x += (dx / dist) * speed;
            rect.y += (dy / dist) * speed;
        }
        break;
    }
    default: break;
    }
}

void Bobber::pullLine(float dt) {
    // Игрок нажал SPACE — ослабляем натяжение
    tension -= dt * 0.45f;
    slack = 0.0f;
    if (tension < 0) tension = 0;
}

void Bobber::render(SDL_Renderer* renderer) {
    if (state == BobberState::IDLE || state == BobberState::CAUGHT) return;

    // Тело поплавка
    if (state == BobberState::BITING) {
        SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255);
    }
    else if (state == BobberState::FLYING) {
        SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
    }
    else if (state == BobberState::REELING) {
        // Цвет по натяжению: зелёный -> жёлтый -> красный
        Uint8 rv = (Uint8)(40 + tension * 215);
        Uint8 gv = (Uint8)(200 - tension * 170);
        SDL_SetRenderDrawColor(renderer, rv, gv, 30, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 210, 0, 255);
    }

    SDL_FRect body = { rect.x, rect.y + 4, 14, 10 };
    SDL_RenderFillRect(renderer, &body);

    // Красная верхушка
    SDL_SetRenderDrawColor(renderer, 200, 20, 20, 255);
    SDL_FRect top = { rect.x + 2, rect.y, 10, 6 };
    SDL_RenderFillRect(renderer, &top);

    // Антенна
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderLine(renderer, (int)(rect.x + 6), (int)(rect.y), (int)(rect.x + 6), (int)(rect.y - 10));

    // Белый блик
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
    SDL_FRect dot = { rect.x + 2, rect.y + 5, 3, 3 };
    SDL_RenderFillRect(renderer, &dot);
}

void Bobber::startReeling() {
    if (state == BobberState::BITING) {
        state = BobberState::REELING;
        tension = 0.0f;
        slack = 0.0f;
        lineBroken = false;
        std::cout << "Reeling!\n";
    }
}

void Bobber::resetCatch() {
    caught = false;
    lineBroken = false;
    tension = 0;
    state = BobberState::IDLE;
    rect.x = homeX; rect.y = homeY;
}

bool Bobber::isCaught() const { return caught; }
Fish Bobber::getCaughtFish() const { return pendingFish; }

float Bobber::getBiteProgress() const {
    if (state != BobberState::FLOATING) return 0.0f;
    return waitTimer.getElapsed() / pendingFish.biteDelay;
}