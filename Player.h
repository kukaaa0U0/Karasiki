#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "InputHandler.h"
#include "FishingRod.h"

enum class PlayerState { IDLE, CASTING, WAITING, REELING };
enum class BoatSkin  { WOOD = 0, METAL = 1, LUXURY = 2 };
enum class RodSkin   { BASIC = 0, CARBON = 1, GOLDEN = 2 };

struct ShopItem {
    std::string name;
    int         cost;
    bool        unlocked = false;
};

class Player {
public:
    Player();
    ~Player();

    void init(float x, float y, float width, float height);
    void update(float dt, const InputHandler& input, float mouseX, float mouseY, bool mouseClicked);
    void render(SDL_Renderer* renderer);
    void clean();

    PlayerState getState()          const { return currentState; }
    const std::vector<std::string>& getCatch() const { return caughtFish; }
    int         getTotalScore()     const { return totalScore; }
    BobberState getBobberState()    const { return rod.getBobberState(); }
    float       getBiteProgress()   const { return rod.getBiteProgress(); }
    float       getTension()        const { return rod.getTension(); }
    bool        hadLineBroken()     const { return rod.hadLineBroken(); }
    void        clearLineBroke()          { rod.clearLineBroke(); }

    float getX() const { return destRect.x; }
    float getY() const { return destRect.y; }

    // Магазин
    BoatSkin    boatSkin = BoatSkin::WOOD;
    RodSkin     rodSkin  = RodSkin::BASIC;
    int         location = 0; // 0=река 1=озеро 2=море

    bool buyBoat(int idx);
    bool buyRod (int idx);
    bool buyLocation(int idx);

    std::string lastCatch;
    bool        newCatch = false;

private:
    SDL_FRect   destRect     = { 0,0,0,0 };
    PlayerState currentState = PlayerState::IDLE;
    FishingRod  rod;
    std::vector<std::string> caughtFish;
    int         totalScore   = 0;

    static constexpr float WATER_LEFT  = 20.0f;
    static constexpr float WATER_RIGHT = 700.0f;
    static constexpr float MOVE_SPEED  = 160.0f;
};