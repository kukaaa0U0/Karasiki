#include "CalmWaters.h"
#include <cmath>
#include <string>
#include <sstream>
#include <cstdlib>

// ═══════════════════════════════════════════════════════════════
//  BITMAP FONT  (5x7 pixels per glyph, scale-able)
//  Glyphs for ASCII 32..126
// ═══════════════════════════════════════════════════════════════
namespace BitmapFont {

    // Each entry = 5 bytes representing columns 0-4, bit0 = top row
    static const uint8_t glyphs[][5] = {
        // 32 space
        {0x00,0x00,0x00,0x00,0x00},
        // 33 !
        {0x00,0x00,0x5F,0x00,0x00},
        // 34 "
        {0x00,0x07,0x00,0x07,0x00},
        // 35 #
        {0x14,0x7F,0x14,0x7F,0x14},
        // 36 $
        {0x24,0x2A,0x7F,0x2A,0x12},
        // 37 %
        {0x23,0x13,0x08,0x64,0x62},
        // 38 &
        {0x36,0x49,0x55,0x22,0x50},
        // 39 '
        {0x00,0x05,0x03,0x00,0x00},
        // 40 (
        {0x00,0x1C,0x22,0x41,0x00},
        // 41 )
        {0x00,0x41,0x22,0x1C,0x00},
        // 42 *
        {0x08,0x2A,0x1C,0x2A,0x08},
        // 43 +
        {0x08,0x08,0x3E,0x08,0x08},
        // 44 ,
        {0x00,0x50,0x30,0x00,0x00},
        // 45 -
        {0x08,0x08,0x08,0x08,0x08},
        // 46 .
        {0x00,0x60,0x60,0x00,0x00},
        // 47 /
        {0x20,0x10,0x08,0x04,0x02},
        // 48 0
        {0x3E,0x51,0x49,0x45,0x3E},
        // 49 1
        {0x00,0x42,0x7F,0x40,0x00},
        // 50 2
        {0x42,0x61,0x51,0x49,0x46},
        // 51 3
        {0x21,0x41,0x45,0x4B,0x31},
        // 52 4
        {0x18,0x14,0x12,0x7F,0x10},
        // 53 5
        {0x27,0x45,0x45,0x45,0x39},
        // 54 6
        {0x3C,0x4A,0x49,0x49,0x30},
        // 55 7
        {0x01,0x71,0x09,0x05,0x03},
        // 56 8
        {0x36,0x49,0x49,0x49,0x36},
        // 57 9
        {0x06,0x49,0x49,0x29,0x1E},
        // 58 :
        {0x00,0x36,0x36,0x00,0x00},
        // 59 ;
        {0x00,0x56,0x36,0x00,0x00},
        // 60 <
        {0x00,0x08,0x14,0x22,0x41},
        // 61 =
        {0x14,0x14,0x14,0x14,0x14},
        // 62 >
        {0x41,0x22,0x14,0x08,0x00},
        // 63 ?
        {0x02,0x01,0x51,0x09,0x06},
        // 64 @
        {0x32,0x49,0x79,0x41,0x3E},
        // 65 A
        {0x7E,0x11,0x11,0x11,0x7E},
        // 66 B
        {0x7F,0x49,0x49,0x49,0x36},
        // 67 C
        {0x3E,0x41,0x41,0x41,0x22},
        // 68 D
        {0x7F,0x41,0x41,0x22,0x1C},
        // 69 E
        {0x7F,0x49,0x49,0x49,0x41},
        // 70 F
        {0x7F,0x09,0x09,0x09,0x01},
        // 71 G
        {0x3E,0x41,0x41,0x51,0x32},
        // 72 H
        {0x7F,0x08,0x08,0x08,0x7F},
        // 73 I
        {0x00,0x41,0x7F,0x41,0x00},
        // 74 J
        {0x20,0x40,0x41,0x3F,0x01},
        // 75 K
        {0x7F,0x08,0x14,0x22,0x41},
        // 76 L
        {0x7F,0x40,0x40,0x40,0x40},
        // 77 M
        {0x7F,0x02,0x04,0x02,0x7F},
        // 78 N
        {0x7F,0x04,0x08,0x10,0x7F},
        // 79 O
        {0x3E,0x41,0x41,0x41,0x3E},
        // 80 P
        {0x7F,0x09,0x09,0x09,0x06},
        // 81 Q
        {0x3E,0x41,0x51,0x21,0x5E},
        // 82 R
        {0x7F,0x09,0x19,0x29,0x46},
        // 83 S
        {0x46,0x49,0x49,0x49,0x31},
        // 84 T
        {0x01,0x01,0x7F,0x01,0x01},
        // 85 U
        {0x3F,0x40,0x40,0x40,0x3F},
        // 86 V
        {0x1F,0x20,0x40,0x20,0x1F},
        // 87 W
        {0x3F,0x40,0x38,0x40,0x3F},
        // 88 X
        {0x63,0x14,0x08,0x14,0x63},
        // 89 Y
        {0x03,0x04,0x78,0x04,0x03},
        // 90 Z
        {0x61,0x51,0x49,0x45,0x43},
        // 91 [
        {0x00,0x00,0x7F,0x41,0x41},
        // 92 backslash
        {0x02,0x04,0x08,0x10,0x20},
        // 93 ]
        {0x41,0x41,0x7F,0x00,0x00},
        // 94 ^
        {0x04,0x02,0x01,0x02,0x04},
        // 95 _
        {0x40,0x40,0x40,0x40,0x40},
        // 96 `
        {0x00,0x01,0x02,0x04,0x00},
        // 97 a
        {0x20,0x54,0x54,0x54,0x78},
        // 98 b
        {0x7F,0x48,0x44,0x44,0x38},
        // 99 c
        {0x38,0x44,0x44,0x44,0x20},
        // 100 d
        {0x38,0x44,0x44,0x48,0x7F},
        // 101 e
        {0x38,0x54,0x54,0x54,0x18},
        // 102 f
        {0x08,0x7E,0x09,0x01,0x02},
        // 103 g
        {0x08,0x14,0x54,0x54,0x3C},
        // 104 h
        {0x7F,0x08,0x04,0x04,0x78},
        // 105 i
        {0x00,0x44,0x7D,0x40,0x00},
        // 106 j
        {0x20,0x40,0x44,0x3D,0x00},
        // 107 k
        {0x00,0x7F,0x10,0x28,0x44},
        // 108 l
        {0x00,0x41,0x7F,0x40,0x00},
        // 109 m
        {0x7C,0x04,0x18,0x04,0x78},
        // 110 n
        {0x7C,0x08,0x04,0x04,0x78},
        // 111 o
        {0x38,0x44,0x44,0x44,0x38},
        // 112 p
        {0x7C,0x14,0x14,0x14,0x08},
        // 113 q
        {0x08,0x14,0x14,0x18,0x7C},
        // 114 r
        {0x7C,0x08,0x04,0x04,0x08},
        // 115 s
        {0x48,0x54,0x54,0x54,0x20},
        // 116 t
        {0x04,0x3F,0x44,0x40,0x20},
        // 117 u
        {0x3C,0x40,0x40,0x20,0x7C},
        // 118 v
        {0x1C,0x20,0x40,0x20,0x1C},
        // 119 w
        {0x3C,0x40,0x30,0x40,0x3C},
        // 120 x
        {0x44,0x28,0x10,0x28,0x44},
        // 121 y
        {0x0C,0x50,0x50,0x50,0x3C},
        // 122 z
        {0x44,0x64,0x54,0x4C,0x44},
        // 123 {
        {0x00,0x08,0x36,0x41,0x00},
        // 124 |
        {0x00,0x00,0x7F,0x00,0x00},
        // 125 }
        {0x00,0x41,0x36,0x08,0x00},
        // 126 ~
        {0x08,0x04,0x08,0x10,0x08},
    };

    void drawChar(SDL_Renderer* r, char c, int x, int y, SDL_Color col, int scale) {
        int idx = (int)(unsigned char)c - 32;
        if (idx < 0 || idx > 94) idx = 0;
        const uint8_t* g = glyphs[idx];
        SDL_SetRenderDrawColor(r, col.r, col.g, col.b, col.a);
        for (int col_ = 0; col_ < 5; ++col_) {
            for (int row = 0; row < 7; ++row) {
                if (g[col_] & (1 << row)) {
                    SDL_FRect px = { (float)(x + col_ * scale), (float)(y + row * scale),
                                     (float)scale, (float)scale };
                    SDL_RenderFillRect(r, &px);
                }
            }
        }
    }

    void drawString(SDL_Renderer* r, const char* s, int x, int y, SDL_Color col, int scale) {
        int cx = x;
        for (; *s; ++s) {
            drawChar(r, *s, cx, y, col, scale);
            cx += (5 + 1) * scale;
        }
    }

    int stringWidth(const char* s, int scale) {
        int n = 0;
        for (; *s; ++s) ++n;
        return n * 6 * scale;
    }

    void drawStringCentered(SDL_Renderer* r, const char* s, int cx, int y, SDL_Color col, int scale) {
        int w = stringWidth(s, scale);
        drawString(r, s, cx - w / 2, y, col, scale);
    }

} // namespace BitmapFont

// ═══════════════════════════════════════════════════════════════
//  CalmWaters
// ═══════════════════════════════════════════════════════════════

CalmWaters::CalmWaters() {
    // Init clouds
    clouds[0] = { 60,  50, 120, 18 };
    clouds[1] = { 300, 30, 160, 12 };
    clouds[2] = { 550, 70,  90, 22 };
    clouds[3] = { 130, 80, 100, 15 };
    clouds[4] = { 680, 45, 110, 20 };
}

CalmWaters::~CalmWaters() { clean(); }

bool CalmWaters::init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) { std::cerr << "Window error: " << SDL_GetError() << std::endl; return false; }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) { std::cerr << "Renderer error: " << SDL_GetError() << std::endl; return false; }

    isRunning = true;
    lastTick = SDL_GetTicks();

    player = new Player();
    player->init(350.0f, 390.0f, 100.0f, 45.0f);

    std::cout << "=== Calm Waters ===" << std::endl;
    std::cout << "A/D or Arrows : move boat" << std::endl;
    std::cout << "SPACE         : cast / reel" << std::endl;
    std::cout << "ESC           : quit" << std::endl;
    return true;
}

void CalmWaters::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) isRunning = false;
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            isRunning = false;
    }
    inputHandler.update();
}

void CalmWaters::update() {
    Uint64 now = SDL_GetTicks();
    float  dt = (now - lastTick) / 1000.0f;
    if (dt > 0.1f) dt = 0.1f;
    lastTick = now;

    waveOffset += dt * 40.0f;
    if (waveOffset > 60.0f) waveOffset -= 60.0f;

    biteFlashTimer += dt;
    if (biteFlashTimer >= 0.25f) {
        biteFlashTimer = 0.0f;
        biteVisible = !biteVisible;
    }

    // Move clouds
    for (auto& c : clouds) {
        c.x += c.speed * dt;
        if (c.x > WIN_W + 100) c.x = -c.w - 10;
    }

    if (player) player->update(dt, inputHandler);
}

// ─── background ──────────────────────────────────────────────────────────────

void CalmWaters::renderBackground() {
    // Sky gradient
    for (int y = 0; y < (int)WATER_Y; ++y) {
        float t = (float)y / WATER_Y;
        Uint8 rv = (Uint8)(170 - t * 80);
        Uint8 gv = (Uint8)(210 - t * 60);
        Uint8 bv = (Uint8)(255 - t * 40);
        SDL_SetRenderDrawColor(renderer, rv, gv, bv, 255);
        SDL_RenderLine(renderer, 0, y, WIN_W, y);
    }

    // Sun
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 240, 100, 60);
    for (int r = 55; r >= 0; r -= 5) {
        SDL_FRect sun = { 680.0f - r, 55.0f - r, (float)(r * 2), (float)(r * 2) };
        SDL_RenderFillRect(renderer, &sun);
    }
    SDL_SetRenderDrawColor(renderer, 255, 245, 150, 255);
    SDL_FRect sunCore = { 648, 23, 64, 64 };
    SDL_RenderFillRect(renderer, &sunCore);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Sun rays
    SDL_SetRenderDrawColor(renderer, 255, 240, 120, 120);
    float sx = 680, sy = 55;
    for (int i = 0; i < 8; ++i) {
        float angle = i * (3.14159f / 4.0f) + waveOffset * 0.01f;
        SDL_RenderLine(renderer,
            (int)sx, (int)sy,
            (int)(sx + std::cos(angle) * 55), (int)(sy + std::sin(angle) * 55));
    }

    // Clouds
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (const auto& c : clouds) {
        // Main cloud body
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
        SDL_FRect cb = { c.x, c.y, c.w, c.w * 0.4f };
        SDL_RenderFillRect(renderer, &cb);
        // Top bumps
        SDL_SetRenderDrawColor(renderer, 240, 240, 255, 200);
        SDL_FRect b1 = { c.x + c.w * 0.1f, c.y - c.w * 0.18f, c.w * 0.3f, c.w * 0.3f };
        SDL_FRect b2 = { c.x + c.w * 0.35f, c.y - c.w * 0.25f, c.w * 0.38f, c.w * 0.38f };
        SDL_FRect b3 = { c.x + c.w * 0.62f, c.y - c.w * 0.15f, c.w * 0.28f, c.w * 0.28f };
        SDL_RenderFillRect(renderer, &b1);
        SDL_RenderFillRect(renderer, &b2);
        SDL_RenderFillRect(renderer, &b3);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Far shore (hills)
    for (int i = 0; i < 3; ++i) {
        float hx = i * 300.0f - 50;
        float hh = 60.0f + i * 15;
        SDL_SetRenderDrawColor(renderer, 40 + i * 10, 100 + i * 8, 50, 255);
        for (int x = 0; x < 360; ++x) {
            float fx = (float)x / 360.0f * 3.14159f;
            float hy = hh * std::sin(fx);
            SDL_RenderLine(renderer,
                (int)(hx + x), (int)(WATER_Y - hy),
                (int)(hx + x), (int)(WATER_Y));
        }
    }

    // Shore line - sandy bank
    SDL_SetRenderDrawColor(renderer, 60, 130, 60, 255);
    SDL_FRect farShore = { 0, WATER_Y - 6, (float)WIN_W, 8 };
    SDL_RenderFillRect(renderer, &farShore);

    // Trees
    int treeX[] = { 20, 85, 170, 260, 360, 460, 560, 650, 740 };
    for (int tx : treeX) {
        // Trunk
        SDL_SetRenderDrawColor(renderer, 110, 75, 30, 255);
        SDL_FRect trunk = { (float)tx + 3, WATER_Y - 52, 7, 22 };
        SDL_RenderFillRect(renderer, &trunk);
        // Crown layers (triangle-ish using rects)
        SDL_SetRenderDrawColor(renderer, 25, 110, 35, 255);
        SDL_FRect c1 = { (float)tx - 6,  WATER_Y - 70, 25, 20 };
        SDL_FRect c2 = { (float)tx - 3,  WATER_Y - 83, 19, 16 };
        SDL_FRect c3 = { (float)tx,      WATER_Y - 93, 13, 12 };
        SDL_RenderFillRect(renderer, &c1);
        SDL_SetRenderDrawColor(renderer, 35, 140, 45, 255);
        SDL_RenderFillRect(renderer, &c2);
        SDL_SetRenderDrawColor(renderer, 50, 160, 55, 255);
        SDL_RenderFillRect(renderer, &c3);
    }

    // Water gradient
    for (int y = (int)WATER_Y; y < WIN_H; ++y) {
        float t = (float)(y - WATER_Y) / (WIN_H - WATER_Y);
        Uint8 rv = (Uint8)(15 + t * 10);
        Uint8 gv = (Uint8)(60 + t * 30);
        Uint8 bv = (Uint8)(110 + t * 40);
        SDL_SetRenderDrawColor(renderer, rv, gv, bv, 255);
        SDL_RenderLine(renderer, 0, y, WIN_W, y);
    }

    // Water waves
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int wave = 0; wave < 7; ++wave) {
        float wy = WATER_Y + 18 + wave * 40;
        SDL_SetRenderDrawColor(renderer, 100, 170, 220, 50 + wave * 5);
        for (int x = 0; x < WIN_W; x += 3) {
            float wx = x + waveOffset * 0.8f + wave * 17;
            float offset = std::sin(wx * 0.045f) * 5.0f + std::sin(wx * 0.02f) * 2.5f;
            SDL_FRect wl = { (float)x, wy + offset, 28, 2 };
            SDL_RenderFillRect(renderer, &wl);
        }
    }

    // Sun reflection on water
    for (int i = 0; i < 6; ++i) {
        float rx = 590.0f + i * 22.0f + std::sin(waveOffset * 0.04f + i) * 15.0f;
        float ry = WATER_Y + 10 + i * 14;
        float rw = 50.0f - i * 6;
        SDL_SetRenderDrawColor(renderer, 255, 240, 130, 60 - i * 8);
        SDL_FRect glint = { rx, ry, rw, 3 };
        SDL_RenderFillRect(renderer, &glint);
    }

    // Generic water sparkles
    for (int i = 0; i < 5; ++i) {
        float rx = 80.0f + i * 140.0f + std::sin(waveOffset * 0.02f + i) * 20.0f;
        float ry = WATER_Y + 15 + i * 8;
        SDL_SetRenderDrawColor(renderer, 200, 230, 255, 40);
        SDL_FRect glint = { rx, ry, 40, 3 };
        SDL_RenderFillRect(renderer, &glint);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Lily pads
    SDL_SetRenderDrawColor(renderer, 30, 120, 30, 255);
    int lilyX[] = { 60, 220, 540, 720 };
    for (int lx : lilyX) {
        SDL_FRect lily = { (float)lx, WATER_Y + 30, 28, 10 };
        SDL_RenderFillRect(renderer, &lily);
        SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255);
        SDL_FRect flower = { (float)lx + 10, WATER_Y + 24, 8, 8 };
        SDL_RenderFillRect(renderer, &flower);
        SDL_SetRenderDrawColor(renderer, 30, 120, 30, 255);
    }
}

// ─── HUD ─────────────────────────────────────────────────────────────────────

void CalmWaters::renderHUD() {
    if (!player) return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 20, 40, 160);
    SDL_FRect panel = { 8, 8, 210, 72 };
    SDL_RenderFillRect(renderer, &panel);
    // Border
    SDL_SetRenderDrawColor(renderer, 80, 160, 200, 200);
    SDL_RenderRect(renderer, &panel);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color yellow = { 255, 230, 60, 255 };
    SDL_Color white = { 220, 240, 255, 255 };

    std::string scoreStr = "SCORE: " + std::to_string(player->getTotalScore());
    BitmapFont::drawString(renderer, scoreStr.c_str(), 16, 16, yellow, 2);

    std::string fishStr = "FISH:  " + std::to_string(player->getCatch().size());
    BitmapFont::drawString(renderer, fishStr.c_str(), 16, 48, white, 2);

    renderStatusBar();
}

void CalmWaters::renderStatusBar() {
    if (!player) return;

    BobberState bs = player->getBobberState();

    // Bottom bar
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 20, 40, 180);
    SDL_FRect bar = { 0, WIN_H - 44, (float)WIN_W, 44 };
    SDL_RenderFillRect(renderer, &bar);
    SDL_SetRenderDrawColor(renderer, 60, 120, 180, 150);
    SDL_FRect barBorder = { 0, WIN_H - 44, (float)WIN_W, 2 };
    SDL_RenderFillRect(renderer, &barBorder);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color white = { 220, 240, 255, 255 };
    SDL_Color yellow = { 255, 230, 60,  255 };
    SDL_Color green = { 80, 220,  80, 255 };
    SDL_Color red = { 255,  80,  80, 255 };
    SDL_Color cyan = { 100, 200, 255, 255 };
    SDL_Color dim = { 150, 160, 180, 255 };

    switch (bs) {
    case BobberState::IDLE:
    case BobberState::CAUGHT:
        BitmapFont::drawStringCentered(renderer, "[ SPACE ] - Cast", WIN_W / 2, WIN_H - 32, white, 2);
        break;

    case BobberState::FLYING:
        BitmapFont::drawStringCentered(renderer, "Casting...", WIN_W / 2, WIN_H - 32, yellow, 2);
        break;

    case BobberState::FLOATING: {
        float prog = player->getBiteProgress();
        float barW = 320.0f;
        float barX = (WIN_W - barW) * 0.5f;
        float barY = WIN_H - 32.0f;

        SDL_SetRenderDrawColor(renderer, 40, 50, 60, 255);
        SDL_FRect bg = { barX - 2, barY - 2, barW + 4, 14 };
        SDL_RenderFillRect(renderer, &bg);

        // Animated fill colour: green -> yellow -> orange as filling up
        Uint8 cr = (Uint8)(40 + prog * 200);
        Uint8 cg = (Uint8)(180 - prog * 60);
        SDL_SetRenderDrawColor(renderer, cr, cg, 40, 255);
        SDL_FRect fill = { barX, barY, barW * prog, 10 };
        SDL_RenderFillRect(renderer, &fill);

        SDL_Color wlbl = { 160, 200, 160, 255 };
        BitmapFont::drawString(renderer, "Waiting...", (int)(barX - 120), WIN_H - 32, wlbl, 2);
        break;
    }

    case BobberState::BITING:
        if (biteVisible) {
            SDL_Color biteColor = { 255, 60, 60, 255 };
            BitmapFont::drawStringCentered(renderer, "!!! BITE !!! Press SPACE", WIN_W / 2, WIN_H - 34, biteColor, 2);
        }
        break;

    case BobberState::REELING:
        BitmapFont::drawStringCentered(renderer, "Reeling in...", WIN_W / 2, WIN_H - 32, cyan, 2);
        break;
    }

    BitmapFont::drawString(renderer, "A/D - Move", WIN_W - 112, WIN_H - 32, dim, 2);
}

void CalmWaters::renderCatchList() {
    if (!player) return;
    const auto& catches = player->getCatch();
    if (catches.empty()) return;

    int maxShow = 6;
    int n = (int)catches.size();
    int show = n > maxShow ? maxShow : n;
    int startIdx = n - show;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 20, 40, 160);
    SDL_FRect panel = { WIN_W - 220.0f, 8, 212, 18.0f + show * 18 + 6 };
    SDL_RenderFillRect(renderer, &panel);
    SDL_SetRenderDrawColor(renderer, 80, 160, 200, 200);
    SDL_RenderRect(renderer, &panel);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color header = { 255, 200, 80, 255 };
    SDL_Color entry = { 180, 230, 180, 255 };
    BitmapFont::drawString(renderer, "CATCH LIST:", WIN_W - 214, 14, header, 1);

    int y = 30;
    for (int i = startIdx; i < n; ++i) {
        BitmapFont::drawString(renderer, catches[i].c_str(), WIN_W - 214, y, entry, 1);
        y += 18;
    }
}

void CalmWaters::render() {
    SDL_SetRenderDrawColor(renderer, 10, 40, 80, 255);
    SDL_RenderClear(renderer);

    renderBackground();
    if (player) player->render(renderer);
    renderHUD();
    renderCatchList();

    SDL_RenderPresent(renderer);
}

void CalmWaters::clean() {
    if (player) { delete player; player = nullptr; }
    if (renderer) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
    if (window) { SDL_DestroyWindow(window);     window = nullptr; }
    SDL_Quit();
    std::cout << "Game closed cleanly." << std::endl;
}

int main(int argc, char* argv[]) {
    CalmWaters game;
    if (game.init("Calm Waters - Fishing", 800, 600)) {
        while (game.running()) {
            game.handleEvents();
            game.update();
            game.render();
            SDL_Delay(16);
        }
    }
    game.clean();
    return 0;
}