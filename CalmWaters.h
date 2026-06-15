#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "Player.h"
#include "InputHandler.h"

enum class GameState {
    PLAYING,
    PAUSED,
    GAME_OVER
};

// ─── Tiny bitmap font (5x7 per glyph) ───────────────────────────────────────
// Each glyph is 5 columns x 7 rows, packed as 5 bytes (one per column, bit0=top)
namespace BitmapFont {
    // ASCII 32..126
    extern const uint8_t glyphs[][5];
    void drawChar(SDL_Renderer* r, char c, int x, int y, SDL_Color col, int scale = 1);
    void drawString(SDL_Renderer* r, const char* s, int x, int y, SDL_Color col, int scale = 1);
    int  stringWidth(const char* s, int scale = 1);
    void drawStringCentered(SDL_Renderer* r, const char* s, int cx, int y, SDL_Color col, int scale = 1);
}

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
    Uint64 lastTick = 0;
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Player* player = nullptr;
    InputHandler  inputHandler;
    GameState     gameState = GameState::PLAYING;

    float waveOffset = 0.0f;
    float biteFlashTimer = 0.0f;
    bool  biteVisible = true;

    // Cloud animation
    struct Cloud { float x, y, w, speed; };
    Cloud clouds[5];

    void renderBackground();
    void renderHUD();
    void renderCatchList();
    void renderStatusBar();

    static constexpr int   WIN_W = 800;
    static constexpr int   WIN_H = 600;
    static constexpr float WATER_Y = 300.0f;
};