#pragma once
#include <SDL3/SDL.h>

class InputHandler {
public:
    // Обновляет состояние всех кнопок
    void update();

    // Проверяет, нажата ли конкретная кнопка прямо сейчас
    bool isKeyDown(SDL_Scancode key) const;

private:
    const bool* keyboardState = nullptr;
};