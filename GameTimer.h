#pragma once
#include <SDL3/SDL.h>

class GameTimer {
public:
    void start();
    bool hasElapsed(float seconds) const;
    float getElapsed() const;

private:
    Uint64 startTick = 0;
};