#include "InputHandler.h"

void InputHandler::update() {
    // SDL_PollEvent убран отсюда — события обрабатываются только в CalmWaters::handleEvents()
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (keyboardState != nullptr) {
        return keyboardState[key];
    }
    return false;
}