#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "Player.h"

class CalmWaters {
public:
    CalmWaters();
    ~CalmWaters();

    // Основные этапы жизненного цикла игры
    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    // Проверка, работает ли еще игра
    bool running() const { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    
    // Сюда мы спрятали нашего рыбака, чтобы к нему был доступ только изнутри игры
    Player* player;
};