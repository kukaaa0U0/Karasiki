#include "Player.h"
#include <iostream>

Player::Player() {
    destRect = { 0.0f, 0.0f, 0.0f, 0.0f };
    currentState = PlayerState::IDLE;
    totalScore = 0;
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
    rod.init(x, y);
}

void Player::update(float dt, const InputHandler& input) {
    float dx = 0;
    if (input.isKeyDown(SDL_SCANCODE_D) || input.isKeyDown(SDL_SCANCODE_RIGHT)) dx += MOVE_SPEED * dt;
    if (input.isKeyDown(SDL_SCANCODE_A) || input.isKeyDown(SDL_SCANCODE_LEFT))  dx -= MOVE_SPEED * dt;

    destRect.x += dx;

    // Не выходим за границы воды
    if (destRect.x < WATER_LEFT)                    destRect.x = WATER_LEFT;
    if (destRect.x + destRect.w > WATER_RIGHT)      destRect.x = WATER_RIGHT - destRect.w;

    // Синхронизируем позицию удочки с лодкой
    rod.syncPosition(destRect.x, destRect.y);

    rod.update(dt, input);

    if (rod.hasCatch()) {
        Fish f = rod.collectFish();
        int pts = f.getScore();
        totalScore += pts;
        caughtFish.push_back(f.toString() + " (+" + std::to_string(pts) + " pts)");
        std::cout << "Caught: " << f.toString() << " +" << pts << " pts | Total: " << totalScore << std::endl;
    }

    // Синхронизируем PlayerState с состоянием поплавка
    BobberState bs = rod.getBobberState();
    switch (bs) {
    case BobberState::IDLE:    currentState = PlayerState::IDLE;    break;
    case BobberState::FLYING:  currentState = PlayerState::CASTING; break;
    case BobberState::FLOATING:currentState = PlayerState::WAITING; break;
    case BobberState::BITING:  currentState = PlayerState::WAITING; break;
    case BobberState::REELING: currentState = PlayerState::REELING; break;
    default: break;
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    // Тень лодки
    SDL_SetRenderDrawColor(renderer, 80, 40, 10, 100);
    SDL_FRect shadow = { destRect.x + 5, destRect.y + destRect.h - 4, destRect.w - 4, 8 };
    SDL_RenderFillRect(renderer, &shadow);

    // Корпус лодки — коричневый
    SDL_SetRenderDrawColor(renderer, 139, 90, 43, 255);
    SDL_RenderFillRect(renderer, &destRect);

    // Борт лодки (светлее)
    SDL_SetRenderDrawColor(renderer, 180, 120, 60, 255);
    SDL_FRect top = { destRect.x, destRect.y, destRect.w, 8 };
    SDL_RenderFillRect(renderer, &top);

    // Человечек на лодке
    SDL_SetRenderDrawColor(renderer, 60, 120, 200, 255);   // синяя фигурка
    SDL_FRect body = { destRect.x + 10, destRect.y - 22, 14, 18 };
    SDL_RenderFillRect(renderer, &body);

    SDL_SetRenderDrawColor(renderer, 255, 220, 170, 255);  // голова
    SDL_FRect head = { destRect.x + 12, destRect.y - 34, 10, 10 };
    SDL_RenderFillRect(renderer, &head);

    rod.render(renderer);
}

void Player::clean() {
    std::cout << "Player cleaned. Fish: " << caughtFish.size() << " Score: " << totalScore << std::endl;
}