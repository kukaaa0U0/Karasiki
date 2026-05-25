#include "Player.h"
#include <iostream>

Player::Player() {
    destRect = { 0.0f, 0.0f, 0.0f, 0.0f };
    currentState = PlayerState::IDLE;
}

Player::~Player() {
    clean();
}

void Player::init(float x, float y, float width, float height) {
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    currentState = PlayerState::IDLE;
    std::cout << "Игрок инициализирован на позиции: " << x << ", " << y << std::endl;
}

void Player::update(const InputHandler& input) {
    // Если зажат классный сканкод стрелочки вправо или кнопки D
    if (input.isKeyDown(SDL_SCANCODE_D) || input.isKeyDown(SDL_SCANCODE_RIGHT)) {
        destRect.x += 4.0f; // Лодка плывет вправо
    }
    if (input.isKeyDown(SDL_SCANCODE_A) || input.isKeyDown(SDL_SCANCODE_LEFT)) {
        destRect.x -= 4.0f; // Лодка плывет влево
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    // Выбираем коричневый цвет для лодки (Рыбака)
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);

    // Рисуем заполненный прямоугольник игрока
    SDL_RenderFillRect(renderer, &destRect);
}

void Player::clean() {
    std::cout << "Ресурсы игрока очищены" << std::endl;
}