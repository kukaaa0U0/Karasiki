#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "Player.h"
#include "InputHandler.h"

class CalmWaters {
public:
    CalmWaters();
    ~CalmWaters();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() const { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player* player;
    InputHandler inputHandler;
};