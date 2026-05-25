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

    // Инициализируем удочку от позиции лодки
    rod.init(x, y);

    std::cout << "Игрок инициализирован на позиции: " << x << ", " << y << std::endl;
}

void Player::update(float dt, const InputHandler& input) {
    // Движение лодки стрелками / WASD
    if (input.isKeyDown(SDL_SCANCODE_D) || input.isKeyDown(SDL_SCANCODE_RIGHT)) {
        destRect.x += 4.0f;
    }
    if (input.isKeyDown(SDL_SCANCODE_A) || input.isKeyDown(SDL_SCANCODE_LEFT)) {
        destRect.x -= 4.0f;
    }

    // Обновляем удочку
    rod.update(dt, input);

    // Проверяем, поймали ли рыбу
    if (rod.hasCatch()) {
        Fish f = rod.collectFish();
        caughtFish.push_back(f.toString());
        std::cout << "Улов: " << f.toString() << " (всего: " << caughtFish.size() << ")" << std::endl;
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    // Лодка — коричневый прямоугольник
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_RenderFillRect(renderer, &destRect);

    // Удочка и поплавок
    rod.render(renderer);
}

void Player::clean() {
    std::cout << "Ресурсы игрока очищены. Поймано рыб: " << caughtFish.size() << std::endl;
}