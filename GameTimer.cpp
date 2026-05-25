#include "GameTimer.h"

void GameTimer::start() {
    startTick = SDL_GetTicks();
}

bool GameTimer::hasElapsed(float seconds) const {
    return getElapsed() >= seconds;
}

float GameTimer::getElapsed() const {
    return (SDL_GetTicks() - startTick) / 1000.0f;
}