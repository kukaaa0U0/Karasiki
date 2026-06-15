#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "Player.h"
#include "InputHandler.h"

// ─── Bitmap font (5x7) ───────────────────────────────────────────────────────
namespace BF {
    void draw(SDL_Renderer* r, const char* s, int x, int y, SDL_Color c, int sc = 1);
    void drawC(SDL_Renderer* r, const char* s, int cx, int y, SDL_Color c, int sc = 1);
    int  wide(const char* s, int sc = 1);
}

// ─── Game states ─────────────────────────────────────────────────────────────
enum class GameState { PLAYING, SHOP };

// ─── Main game class ─────────────────────────────────────────────────────────
class CalmWaters {
public:
    CalmWaters();
    ~CalmWaters();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() const { return isRunning; }

private:
    // Core
    Uint64        lastTick = 0;
    bool          isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Player* player = nullptr;
    InputHandler  inputHandler;
    GameState     gameState = GameState::PLAYING;

    // Mouse
    float mouseX = 0, mouseY = 0;
    bool  mouseClick = false;

    // Animation
    float waveOffset = 0;
    float biteFlashTimer = 0;
    bool  biteVisible = true;
    float catchAnim = 0;   // pop-up animation 0..1
    std::string catchMsg;

    // Line-break flash
    float lineBreakTimer = 0;

    struct Cloud { float x, y, w, speed; };
    Cloud clouds[6];

    // Shop
    bool shopKeyWas = false;

    // Audio
    SDL_AudioStream* audioStream = nullptr;
    float audioPhase[4] = {};  // фазы для 4 нот
    float musicTimer = 0;
    int   noteIdx = 0;
    void  generateMusic(float dt);
    static const float NOTES[];

    // Render helpers
    void renderBg();
    void renderHUD();
    void renderStatusBar();
    void renderCatchList();
    void renderShop();
    void renderTensionBar();
    void renderCatchPopup(float dt);

    static constexpr int   WIN_W = 800;
    static constexpr int   WIN_H = 600;
    static constexpr float WATER_Y = 295.0f;
};