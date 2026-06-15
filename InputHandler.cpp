#include "InputHandler.h"

void InputHandler::update() {
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (keyboardState != nullptr) {
        return keyboardState[key];
    }
    return false;
}