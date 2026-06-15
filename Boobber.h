#pragma once
#include <SDL3/SDL.h>
#include "GameTimer.h"
#include "Fish.h"

enum class BobberState {
    IDLE,       // лежит у лодки
    FLYING,     // летит к точке заброса
    FLOATING,   // качаетс€ на воде, ждЄм клЄва
    BITING,     // рыба клюЄт Ч поплавок дЄргаетс€
    REELING,    // т€нем рыбу к берегу
    CAUGHT      // рыба поймана, ждЄм сброса
};

class Bobber {
public:
    void init(float x, float y);
    void cast(float targetX, float targetY);
    void update(float dt);
    void render(SDL_Renderer* renderer);
    void resetCatch();
    void startReeling();

    bool isCaught() const;
    Fish getCaughtFish() const;
    BobberState getState() const { return state; }

    // позици€ поплавка (дл€ леска)
    float getPosX() const { return rect.x + rect.w * 0.5f; }
    float getPosY() const { return rect.y + rect.h * 0.5f; }

    // сколько осталось до клЄва (0..1)
    float getBiteProgress() const;

private:
    SDL_FRect rect = { 0, 0, 14, 14 };
    float homeX = 0, homeY = 0;
    float targetX = 0, targetY = 0;

    // анимаци€ полЄта
    float flyProgress = 0.0f;   // 0..1
    float startX = 0, startY = 0;

    BobberState state = BobberState::IDLE;
    GameTimer waitTimer;
    Fish pendingFish;

    float bobOffset = 0;
    float bobTime = 0;
    bool caught = false;
};