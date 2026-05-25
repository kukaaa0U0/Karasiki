#pragma once
#include <SDL3/SDL.h>
#include "GameTimer.h"
#include "Fish.h"

enum class BobberState {
    IDLE,      // лежит у лодки
    FLYING,    // летит к точке заброса
    FLOATING,  // качаетс€ на воде, ждЄм клЄва
    BITING,    // рыба клюЄт Ч поплавок дЄргаетс€
    REELING    // т€нем рыбу
};

class Bobber {
public:
    void init(float x, float y);
    void cast(float targetX, float targetY);  // заброс
    void update(float dt);
    void render(SDL_Renderer* renderer);
    void resetCatch();

    void startReeling();       // игрок начал т€нуть (нажал пробел при клЄве)
    bool isCaught() const;     // рыба поймана?
    Fish getCaughtFish() const;

    BobberState getState() const { return state; }

private:
    SDL_FRect rect = { 0, 0, 12, 12 };
    float homeX = 0, homeY = 0;   // позици€ у лодки
    float targetX = 0, targetY = 0;

    BobberState state = BobberState::IDLE;
    GameTimer waitTimer;   // таймер ожидани€ клЄва
    Fish pendingFish;      // кака€ рыба будет клевать

    float bobOffset = 0;   // анимаци€ покачивани€
    float bobTime = 0;
    bool caught = false;
};