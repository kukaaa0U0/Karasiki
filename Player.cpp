#include "Player.h"
#include <iostream>

Player::Player() {
    destRect = { 0,0,0,0 };
    currentState = PlayerState::IDLE;
    totalScore = 0;
}
Player::~Player() { clean(); }

void Player::init(float x, float y, float w, float h) {
    destRect = { x, y, w, h };
    rod.init(x, y);
}

void Player::update(float dt, const InputHandler& input,
    float mouseX, float mouseY, bool mouseClicked) {
    newCatch = false;
    float dx = 0;
    if (input.isKeyDown(SDL_SCANCODE_D) || input.isKeyDown(SDL_SCANCODE_RIGHT)) dx += MOVE_SPEED * dt;
    if (input.isKeyDown(SDL_SCANCODE_A) || input.isKeyDown(SDL_SCANCODE_LEFT))  dx -= MOVE_SPEED * dt;
    destRect.x += dx;
    if (destRect.x < WATER_LEFT)               destRect.x = WATER_LEFT;
    if (destRect.x + destRect.w > WATER_RIGHT) destRect.x = WATER_RIGHT - destRect.w;

    rod.syncPosition(destRect.x, destRect.y);
    rod.update(dt, input, mouseX, mouseY, mouseClicked);

    if (rod.hasCatch()) {
        Fish f = rod.collectFish();
        int  pts = f.getScore();
        totalScore += pts;
        lastCatch = f.toString() + " (+" + std::to_string(pts) + ")";
        caughtFish.push_back(lastCatch);
        newCatch = true;
        std::cout << "Caught: " << f.toString() << " +" << pts << " | Total: " << totalScore << "\n";
    }

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

    // Тень лодки (псевдо-3D)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 60);
    SDL_FRect shadow = { destRect.x + 8, destRect.y + destRect.h - 2, destRect.w - 4, 10 };
    SDL_RenderFillRect(renderer, &shadow);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Корпус лодки по скину
    Uint8 br, bg, bb;
    switch (boatSkin) {
    case BoatSkin::METAL:
        br = 120; bg = 130; bb = 140; break;
    case BoatSkin::LUXURY:
        br = 180; bg = 150; bb = 30;  break;
    default:
        br = 139; bg = 90;  bb = 43;  break;
    }
    SDL_SetRenderDrawColor(renderer, br, bg, bb, 255);
    SDL_RenderFillRect(renderer, &destRect);

    // Нижняя часть (псевдо-3D борт снизу)
    SDL_SetRenderDrawColor(renderer, br * 0.6, bg * 0.6, bb * 0.6, 255);
    SDL_FRect bottom = { destRect.x, destRect.y + destRect.h - 10, destRect.w, 10 };
    SDL_RenderFillRect(renderer, &bottom);

    // Верхний борт (светлее)
    SDL_SetRenderDrawColor(renderer, (Uint8)SDL_min(br + 50, 255), (Uint8)SDL_min(bg + 40, 255), (Uint8)SDL_min(bb + 20, 255), 255);
    SDL_FRect top = { destRect.x, destRect.y, destRect.w, 8 };
    SDL_RenderFillRect(renderer, &top);

    // Сиденье в лодке
    SDL_SetRenderDrawColor(renderer, (Uint8)SDL_min(br + 20, 255), (Uint8)SDL_min(bg + 10, 255), (Uint8)SDL_min(bb + 5, 255), 255);
    SDL_FRect seat = { destRect.x + 30, destRect.y + 12, 40, 8 };
    SDL_RenderFillRect(renderer, &seat);

    // Человечек
    SDL_SetRenderDrawColor(renderer, 60, 120, 200, 255);
    SDL_FRect body = { destRect.x + 10, destRect.y - 22, 14, 18 };
    SDL_RenderFillRect(renderer, &body);
    SDL_SetRenderDrawColor(renderer, 255, 220, 170, 255);
    SDL_FRect head = { destRect.x + 12, destRect.y - 34, 10, 10 };
    SDL_RenderFillRect(renderer, &head);
    // Шляпа
    SDL_SetRenderDrawColor(renderer, 60, 40, 20, 255);
    SDL_FRect hat = { destRect.x + 10, destRect.y - 40, 14, 6 };
    SDL_RenderFillRect(renderer, &hat);

    rod.render(renderer);
}

void Player::clean() {
    std::cout << "Player cleaned. Fish: " << caughtFish.size() << " Score: " << totalScore << "\n";
}

bool Player::buyBoat(int idx) {
    const int prices[] = { 0, 300, 800 };
    if (idx < 0 || idx > 2) return false;
    if ((int)boatSkin == idx) return false;
    if (totalScore < prices[idx]) return false;
    totalScore -= prices[idx];
    boatSkin = (BoatSkin)idx;
    return true;
}

bool Player::buyRod(int idx) {
    const int prices[] = { 0, 200, 600 };
    if (idx < 0 || idx > 2) return false;
    if ((int)rodSkin == idx) return false;
    if (totalScore < prices[idx]) return false;
    totalScore -= prices[idx];
    rodSkin = (RodSkin)idx;
    return true;
}

bool Player::buyLocation(int idx) {
    const int prices[] = { 0, 400, 1000 };
    if (idx < 0 || idx > 2) return false;
    if (location == idx) return false;
    if (totalScore < prices[idx]) return false;
    totalScore -= prices[idx];
    location = idx;
    return true;
}