#include "CalmWaters.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>

// ═══════════════════════════════════════════════════════════════════════════
//   BITMAP FONT  5x7
// ═══════════════════════════════════════════════════════════════════════════
namespace BF {
    static const uint8_t G[][5] = {
    {0x00,0x00,0x00,0x00,0x00}, // 32 sp
    {0x00,0x00,0x5F,0x00,0x00}, // 33 !
    {0x00,0x07,0x00,0x07,0x00}, // 34 "
    {0x14,0x7F,0x14,0x7F,0x14}, // 35 #
    {0x24,0x2A,0x7F,0x2A,0x12}, // 36 $
    {0x23,0x13,0x08,0x64,0x62}, // 37 %
    {0x36,0x49,0x55,0x22,0x50}, // 38 &
    {0x00,0x05,0x03,0x00,0x00}, // 39 '
    {0x00,0x1C,0x22,0x41,0x00}, // 40 (
    {0x00,0x41,0x22,0x1C,0x00}, // 41 )
    {0x08,0x2A,0x1C,0x2A,0x08}, // 42 *
    {0x08,0x08,0x3E,0x08,0x08}, // 43 +
    {0x00,0x50,0x30,0x00,0x00}, // 44 ,
    {0x08,0x08,0x08,0x08,0x08}, // 45 -
    {0x00,0x60,0x60,0x00,0x00}, // 46 .
    {0x20,0x10,0x08,0x04,0x02}, // 47 /
    {0x3E,0x51,0x49,0x45,0x3E}, // 48 0
    {0x00,0x42,0x7F,0x40,0x00}, // 49 1
    {0x42,0x61,0x51,0x49,0x46}, // 50 2
    {0x21,0x41,0x45,0x4B,0x31}, // 51 3
    {0x18,0x14,0x12,0x7F,0x10}, // 52 4
    {0x27,0x45,0x45,0x45,0x39}, // 53 5
    {0x3C,0x4A,0x49,0x49,0x30}, // 54 6
    {0x01,0x71,0x09,0x05,0x03}, // 55 7
    {0x36,0x49,0x49,0x49,0x36}, // 56 8
    {0x06,0x49,0x49,0x29,0x1E}, // 57 9
    {0x00,0x36,0x36,0x00,0x00}, // 58 :
    {0x00,0x56,0x36,0x00,0x00}, // 59 ;
    {0x08,0x14,0x22,0x41,0x00}, // 60 <
    {0x14,0x14,0x14,0x14,0x14}, // 61 =
    {0x00,0x41,0x22,0x14,0x08}, // 62 >
    {0x02,0x01,0x51,0x09,0x06}, // 63 ?
    {0x32,0x49,0x79,0x41,0x3E}, // 64 @
    {0x7E,0x11,0x11,0x11,0x7E}, // 65 A
    {0x7F,0x49,0x49,0x49,0x36}, // 66 B
    {0x3E,0x41,0x41,0x41,0x22}, // 67 C
    {0x7F,0x41,0x41,0x22,0x1C}, // 68 D
    {0x7F,0x49,0x49,0x49,0x41}, // 69 E
    {0x7F,0x09,0x09,0x09,0x01}, // 70 F
    {0x3E,0x41,0x41,0x51,0x32}, // 71 G
    {0x7F,0x08,0x08,0x08,0x7F}, // 72 H
    {0x00,0x41,0x7F,0x41,0x00}, // 73 I
    {0x20,0x40,0x41,0x3F,0x01}, // 74 J
    {0x7F,0x08,0x14,0x22,0x41}, // 75 K
    {0x7F,0x40,0x40,0x40,0x40}, // 76 L
    {0x7F,0x02,0x04,0x02,0x7F}, // 77 M
    {0x7F,0x04,0x08,0x10,0x7F}, // 78 N
    {0x3E,0x41,0x41,0x41,0x3E}, // 79 O
    {0x7F,0x09,0x09,0x09,0x06}, // 80 P
    {0x3E,0x41,0x51,0x21,0x5E}, // 81 Q
    {0x7F,0x09,0x19,0x29,0x46}, // 82 R
    {0x46,0x49,0x49,0x49,0x31}, // 83 S
    {0x01,0x01,0x7F,0x01,0x01}, // 84 T
    {0x3F,0x40,0x40,0x40,0x3F}, // 85 U
    {0x1F,0x20,0x40,0x20,0x1F}, // 86 V
    {0x3F,0x40,0x38,0x40,0x3F}, // 87 W
    {0x63,0x14,0x08,0x14,0x63}, // 88 X
    {0x03,0x04,0x78,0x04,0x03}, // 89 Y
    {0x61,0x51,0x49,0x45,0x43}, // 90 Z
    {0x00,0x00,0x7F,0x41,0x41}, // 91 [
    {0x02,0x04,0x08,0x10,0x20}, // 92 backslash
    {0x41,0x41,0x7F,0x00,0x00}, // 93 ]
    {0x04,0x02,0x01,0x02,0x04}, // 94 ^
    {0x40,0x40,0x40,0x40,0x40}, // 95 _
    {0x00,0x01,0x02,0x04,0x00}, // 96 `
    {0x20,0x54,0x54,0x54,0x78}, // 97 a
    {0x7F,0x48,0x44,0x44,0x38}, // 98 b
    {0x38,0x44,0x44,0x44,0x20}, // 99 c
    {0x38,0x44,0x44,0x48,0x7F}, //100 d
    {0x38,0x54,0x54,0x54,0x18}, //101 e
    {0x08,0x7E,0x09,0x01,0x02}, //102 f
    {0x08,0x14,0x54,0x54,0x3C}, //103 g
    {0x7F,0x08,0x04,0x04,0x78}, //104 h
    {0x00,0x44,0x7D,0x40,0x00}, //105 i
    {0x20,0x40,0x44,0x3D,0x00}, //106 j
    {0x00,0x7F,0x10,0x28,0x44}, //107 k
    {0x00,0x41,0x7F,0x40,0x00}, //108 l
    {0x7C,0x04,0x18,0x04,0x78}, //109 m
    {0x7C,0x08,0x04,0x04,0x78}, //110 n
    {0x38,0x44,0x44,0x44,0x38}, //111 o
    {0x7C,0x14,0x14,0x14,0x08}, //112 p
    {0x08,0x14,0x14,0x18,0x7C}, //113 q
    {0x7C,0x08,0x04,0x04,0x08}, //114 r
    {0x48,0x54,0x54,0x54,0x20}, //115 s
    {0x04,0x3F,0x44,0x40,0x20}, //116 t
    {0x3C,0x40,0x40,0x20,0x7C}, //117 u
    {0x1C,0x20,0x40,0x20,0x1C}, //118 v
    {0x3C,0x40,0x30,0x40,0x3C}, //119 w
    {0x44,0x28,0x10,0x28,0x44}, //120 x
    {0x0C,0x50,0x50,0x50,0x3C}, //121 y
    {0x44,0x64,0x54,0x4C,0x44}, //122 z
    {0x00,0x08,0x36,0x41,0x00}, //123 {
    {0x00,0x00,0x7F,0x00,0x00}, //124 |
    {0x00,0x41,0x36,0x08,0x00}, //125 }
    {0x08,0x04,0x08,0x10,0x08}, //126 ~
    };

    void draw(SDL_Renderer* r, const char* s, int x, int y, SDL_Color c, int sc) {
        SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
        int cx = x;
        for (;*s;++s) {
            int idx = (int)(unsigned char)*s - 32;
            if (idx < 0 || idx>94) idx = 0;
            const uint8_t* g = G[idx];
            for (int col = 0;col < 5;++col)
                for (int row = 0;row < 7;++row)
                    if (g[col] & (1 << row)) {
                        SDL_FRect px = { (float)(cx + col * sc),(float)(y + row * sc),(float)sc,(float)sc };
                        SDL_RenderFillRect(r, &px);
                    }
            cx += (6) * sc;
        }
    }
    int wide(const char* s, int sc) { int n = 0;for (;*s;++s)++n;return n * 6 * sc; }
    void drawC(SDL_Renderer* r, const char* s, int cx, int y, SDL_Color c, int sc) {
        draw(r, s, cx - wide(s, sc) / 2, y, c, sc);
    }
} // namespace BF

// ═══════════════════════════════════════════════════════════════════════════
//   MUSIC NOTES  (частоты в Hz, пентатоника)
// ═══════════════════════════════════════════════════════════════════════════
const float CalmWaters::NOTES[] = {
    261.63f, 293.66f, 329.63f, 392.00f, 440.00f,  // C4 D E G A  (пентатоника до)
    523.25f, 587.33f, 659.25f, 784.00f, 880.00f,  // октава выше
    196.00f, 220.00f, 246.94f, 293.66f, 329.63f   // октава ниже
};
// Мелодия — индексы нот (рыбацкий мотив)
static const int MELODY[] = {
    0,2,4,2,0, 2,4,7,4,2, 5,7,9,7,5, 0,0,-1,
    4,5,7,5,4, 2,4,5,4,2, 0,2,4,2,0, 0,-1,-1,-1
};
static const float DURATIONS[] = {
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.6f,0.6f,0.9f,
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.3f,0.3f,0.3f,0.3f,0.6f,
    0.6f,0.6f,0.6f,0.9f
};
static constexpr int MELODY_LEN = 37;

// ═══════════════════════════════════════════════════════════════════════════
//  Constructor / Destructor
// ═══════════════════════════════════════════════════════════════════════════
CalmWaters::CalmWaters() {
    clouds[0] = { 50,  40,130,16 };
    clouds[1] = { 280, 25,170,10 };
    clouds[2] = { 520, 65,100,20 };
    clouds[3] = { 140, 75,110,13 };
    clouds[4] = { 670, 40,120,18 };
    clouds[5] = { 400, 90, 80,14 };
}
CalmWaters::~CalmWaters() { clean(); }

// ═══════════════════════════════════════════════════════════════════════════
//  Init
// ═══════════════════════════════════════════════════════════════════════════
bool CalmWaters::init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n"; return false;
    }
    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) { std::cerr << "Window: " << SDL_GetError() << "\n";return false; }
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) { std::cerr << "Renderer: " << SDL_GetError() << "\n";return false; }

    // ─── Audio ───────────────────────────────────────────────────────────
    SDL_AudioSpec spec{};
    spec.format = SDL_AUDIO_F32;
    spec.channels = 1;
    spec.freq = 44100;
    audioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &spec, nullptr, nullptr);
    if (audioStream) {
        SDL_ResumeAudioStreamDevice(audioStream);
    }
    else {
        std::cerr << "Audio init failed (no sound): " << SDL_GetError() << "\n";
    }

    isRunning = true;
    lastTick = SDL_GetTicks();

    player = new Player();
    player->init(350.0f, 385.0f, 100.0f, 45.0f);

    std::cout << "=== Тихие Воды ===\n"
        << "A/D — двигать лодку\n"
        << "ЛКМ — заброс мышью\n"
        << "SPACE — заброс / подсечка / удержание лески\n"
        << "TAB — магазин\n"
        << "ESC — выход\n";
    return true;
}

// ═══════════════════════════════════════════════════════════════════════════
//  Music generation
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::generateMusic(float dt) {
    if (!audioStream) return;

    // Сколько сэмплов нужно заполнить (держим буфер ~0.1с)
    int queued = (int)SDL_GetAudioStreamQueued(audioStream);
    int sr = 44100;
    int need = sr / 10 - queued / (int)sizeof(float);
    if (need <= 0) return;

    static float phase = 0;
    static float phase2 = 0;
    static float noteTime = 0;
    static int   mIdx = 0;

    std::vector<float> buf(need);
    float step = 1.0f / sr;

    for (int i = 0;i < need;++i) {
        noteTime += step;
        if (mIdx < MELODY_LEN && noteTime >= DURATIONS[mIdx]) {
            noteTime = 0;
            mIdx = (mIdx + 1) % MELODY_LEN;
        }

        float sample = 0;
        int ni = (mIdx < MELODY_LEN) ? MELODY[mIdx] : -1;
        if (ni >= 0) {
            float freq = NOTES[ni];
            // Мягкая волна: синус + немного обертонов
            float env = 1.0f - noteTime / (DURATIONS[mIdx < MELODY_LEN ? mIdx : 0] + 0.01f);
            env = env * env; // квадратный огибающий (мягкое затухание)
            sample = 0.18f * std::sin(phase) * env;
            sample += 0.06f * std::sin(phase * 2) * env;
            sample += 0.03f * std::sin(phase * 3) * env;
            // Фоновый "плеск воды" — розовый шум лёгкий
            sample += 0.015f * ((float)(rand() % 1000) / 500.0f - 1.0f);
            phase += 2.0f * 3.14159f * freq * step;
            if (phase > 2.0f * 3.14159f) phase -= 2.0f * 3.14159f;
        }
        else {
            // Пауза
            phase = 0;
        }
        buf[i] = sample;
    }
    SDL_PutAudioStreamData(audioStream, buf.data(), (int)(buf.size() * sizeof(float)));
}

// ═══════════════════════════════════════════════════════════════════════════
//  Handle events
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::handleEvents() {
    mouseClick = false;
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_EVENT_QUIT) isRunning = false;
        if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_ESCAPE) {
            if (gameState == GameState::SHOP) gameState = GameState::PLAYING;
            else isRunning = false;
        }
        if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN && ev.button.button == 1)
            mouseClick = true;
        if (ev.type == SDL_EVENT_MOUSE_MOTION) {
            mouseX = ev.motion.x; mouseY = ev.motion.y;
        }
    }
    inputHandler.update();
}

// ═══════════════════════════════════════════════════════════════════════════
//  Update
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::update() {
    Uint64 now = SDL_GetTicks();
    float dt = (now - lastTick) / 1000.0f;
    if (dt > 0.1f)dt = 0.1f;
    lastTick = now;

    generateMusic(dt);

    waveOffset += dt * 35.0f;
    if (waveOffset > 70.0f)waveOffset -= 70.0f;

    biteFlashTimer += dt;
    if (biteFlashTimer >= 0.22f) { biteFlashTimer = 0;biteVisible = !biteVisible; }

    for (auto& c : clouds) { c.x += c.speed * dt;if (c.x > WIN_W + 120)c.x = -c.w - 10; }

    if (lineBreakTimer > 0) lineBreakTimer -= dt;
    if (catchAnim > 0)      catchAnim -= dt * 0.5f;

    // TAB — магазин
    bool tabNow = inputHandler.isKeyDown(SDL_SCANCODE_TAB);
    if (tabNow && !shopKeyWas) {
        gameState = (gameState == GameState::PLAYING) ? GameState::SHOP : GameState::PLAYING;
    }
    shopKeyWas = tabNow;

    if (gameState == GameState::PLAYING && player) {
        bool clickForFish = mouseClick && mouseY > WATER_Y;
        player->update(dt, inputHandler, mouseX, mouseY, clickForFish);

        if (player->newCatch) {
            catchMsg = player->lastCatch;
            catchAnim = 4.0f;
        }
        if (player->hadLineBroken()) {
            lineBreakTimer = 2.5f;
            player->clearLineBroke();
        }
    }
    else if (gameState == GameState::SHOP && player && mouseClick) {
        // Кнопки магазина (y-позиции рассчитаны под renderShop)
        // Лодки
        if (mouseY > 160 && mouseY < 200) {
            if (mouseX > 60 && mouseX < 160) player->buyBoat(0);
            if (mouseX > 180 && mouseX < 280) player->buyBoat(1);
            if (mouseX > 300 && mouseX < 400) player->buyBoat(2);
        }
        // Удочки
        if (mouseY > 260 && mouseY < 300) {
            if (mouseX > 60 && mouseX < 160) player->buyRod(0);
            if (mouseX > 180 && mouseX < 280) player->buyRod(1);
            if (mouseX > 300 && mouseX < 400) player->buyRod(2);
        }
        // Локации
        if (mouseY > 360 && mouseY < 400) {
            if (mouseX > 60 && mouseX < 160) player->buyLocation(0);
            if (mouseX > 180 && mouseX < 280) player->buyLocation(1);
            if (mouseX > 300 && mouseX < 400) player->buyLocation(2);
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  Render Background
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderBg() {
    int loc = player ? player->location : 0;

    // Sky gradient
    Uint8 skyR[3] = { 170,120,80 }, skyG[3] = { 210,170,120 }, skyB[3] = { 255,220,160 };
    for (int y = 0;y < (int)WATER_Y;++y) {
        float t = (float)y / WATER_Y;
        SDL_SetRenderDrawColor(renderer,
            (Uint8)(skyR[loc] - t * 70), (Uint8)(skyG[loc] - t * 50), (Uint8)(skyB[loc] - t * 40), 255);
        SDL_RenderLine(renderer, 0, y, WIN_W, y);
    }

    // Солнце / луна (для ночного озера)
    if (loc == 2) {
        // Луна
        SDL_SetRenderDrawColor(renderer, 240, 240, 200, 255);
        SDL_FRect moon = { 680,20,50,50 };SDL_RenderFillRect(renderer, &moon);
        SDL_SetRenderDrawColor(renderer, 60, 40, 80, 255);
        SDL_FRect mshad = { 690,20,45,45 };SDL_RenderFillRect(renderer, &mshad);
    }
    else {
        // Солнечное гало
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        for (int ri = 60;ri >= 5;ri -= 5) {
            SDL_SetRenderDrawColor(renderer, 255, 240, 100, (Uint8)(8 + ri / 3));
            SDL_FRect s = { (float)(680 - ri),(float)(55 - ri),(float)(ri * 2),(float)(ri * 2) };
            SDL_RenderFillRect(renderer, &s);
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(renderer, 255, 245, 150, 255);
        SDL_FRect sun = { 648,23,64,64 };SDL_RenderFillRect(renderer, &sun);
        // Лучи
        SDL_SetRenderDrawColor(renderer, 255, 240, 120, 100);
        for (int i = 0;i < 8;++i) {
            float a = i * (3.14159f / 4) + waveOffset * 0.008f;
            SDL_RenderLine(renderer, 680, 55, (int)(680 + cosf(a) * 65), (int)(55 + sinf(a) * 65));
        }
    }

    // Облака
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (auto& c : clouds) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, loc == 2 ? 80 : 200);
        SDL_FRect cb = { c.x,c.y,c.w,c.w * 0.38f };SDL_RenderFillRect(renderer, &cb);
        SDL_FRect b1 = { c.x + c.w * .08f,c.y - c.w * .18f,c.w * .32f,c.w * .32f };
        SDL_FRect b2 = { c.x + c.w * .34f,c.y - c.w * .26f,c.w * .38f,c.w * .38f };
        SDL_FRect b3 = { c.x + c.w * .60f,c.y - c.w * .14f,c.w * .30f,c.w * .30f };
        SDL_RenderFillRect(renderer, &b1);
        SDL_RenderFillRect(renderer, &b2);
        SDL_RenderFillRect(renderer, &b3);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Холмы (псевдо-3D перспектива: дальние холмы светлее и тоньше)
    struct Hill { float x, y, w, h; Uint8 r, g, b; };
    Hill hills[] =
    {
        // дальний план (маленькие)
        {-60, WATER_Y - 45, 280,45, 80,130,70},
        {200, WATER_Y - 35, 260,35, 90,140,80},
        {420, WATER_Y - 50, 300,50, 75,125,65},
        {660, WATER_Y - 38, 200,38, 85,135,75},
        // ближний план (большие, тёмные)
        {-80, WATER_Y - 65, 320,65, 40,100,40},
        {220, WATER_Y - 80, 280,80, 35, 95,35},
        {460, WATER_Y - 70, 340,70, 45,105,45},
    };
    for (auto& h : hills) {
        SDL_SetRenderDrawColor(renderer, h.r, h.g, h.b, 255);
        for (int x = 0;x < (int)h.w;++x) {
            float fx = (float)x / h.w * 3.14159f;
            float hy = h.h * sinf(fx);
            SDL_FRect sl = { (float)(h.x + x),h.y - hy,1,hy + 4 };
            SDL_RenderFillRect(renderer, &sl);
        }
    }

    // Береговая полоса
    SDL_SetRenderDrawColor(renderer, 50, 120, 50, 255);
    SDL_FRect shore = { 0,WATER_Y - 4,(float)WIN_W,8 };SDL_RenderFillRect(renderer, &shore);

    // Деревья
    int txs[] = { 15,75,155,245,350,450,555,645,735 };
    for (int tx : txs) {
        SDL_SetRenderDrawColor(renderer, 100, 65, 25, 255);
        SDL_FRect trunk = { (float)tx + 3,WATER_Y - 52,7,22 };SDL_RenderFillRect(renderer, &trunk);
        SDL_SetRenderDrawColor(renderer, 25, 100, 30, 255);
        SDL_FRect c1 = { (float)tx - 6,WATER_Y - 70,25,22 };SDL_RenderFillRect(renderer, &c1);
        SDL_SetRenderDrawColor(renderer, 35, 130, 40, 255);
        SDL_FRect c2 = { (float)tx - 3,WATER_Y - 84,19,17 };SDL_RenderFillRect(renderer, &c2);
        SDL_SetRenderDrawColor(renderer, 50, 155, 50, 255);
        SDL_FRect c3 = { (float)tx,WATER_Y - 95,13,14 };SDL_RenderFillRect(renderer, &c3);
    }

    // Вода
    Uint8 wR[3] = { 15,10,20 }, wG[3] = { 60,80,50 }, wB[3] = { 110,130,140 };
    for (int y = (int)WATER_Y;y < WIN_H;++y) {
        float t = (float)(y - WATER_Y) / (WIN_H - WATER_Y);
        // Перспективное затемнение — нижние строки темнее
        float depth = 1.0f - t * 0.3f;
        SDL_SetRenderDrawColor(renderer,
            (Uint8)((wR[loc] + t * 12) * depth), (Uint8)((wG[loc] + t * 30) * depth), (Uint8)((wB[loc] + t * 40) * depth), 255);
        SDL_RenderLine(renderer, 0, y, WIN_W, y);
    }

    // Волны (перспективные — дальние тоньше, ближние шире)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int wi = 0;wi < 8;++wi) {
        float wy = WATER_Y + 15 + wi * 36;
        float perspW = 2.0f + wi * 0.5f; // ширина волны растёт
        float perspA = (float)(40 + wi * 8);
        SDL_SetRenderDrawColor(renderer, 120, 180, 230, (Uint8)perspA);
        for (int x = 0;x < WIN_W;x += (int)(2 + wi * 0.3f)) {
            float wx = x + waveOffset * (0.5f + wi * 0.1f) + wi * 19;
            float ofs = sinf(wx * 0.04f) * 5.0f + sinf(wx * 0.018f) * 2.5f;
            SDL_FRect wl = { (float)x,wy + ofs,perspW * (24 - wi * 1.5f),perspW };
            SDL_RenderFillRect(renderer, &wl);
        }
    }

    // Отражение
    for (int i = 0;i < 7;++i) {
        float rx = 600.0f + i * 20 + sinf(waveOffset * 0.035f + i) * 18;
        float ry = WATER_Y + 8 + i * 13;
        SDL_SetRenderDrawColor(renderer, 255, 240, 140, (Uint8)(55 - i * 7));
        SDL_FRect gl = { rx,ry,48.0f - i * 5,3 };SDL_RenderFillRect(renderer, &gl);
    }

    // Кувшинки (только на реке/озере)
    if (loc < 2) {
        int lxs[] = { 55,215,530,715 };
        for (int lx : lxs) {
            SDL_SetRenderDrawColor(renderer, 30, 115, 30, 255);
            SDL_FRect lily = { (float)lx,WATER_Y + 28,30,11 };SDL_RenderFillRect(renderer, &lily);
            SDL_SetRenderDrawColor(renderer, 210, 40, 40, 255);
            SDL_FRect fl = { (float)lx + 10,WATER_Y + 22,9,9 };SDL_RenderFillRect(renderer, &fl);
        }
    }

    // Камыши (только на реке)
    if (loc == 0) {
        int rxs[] = { 38,42,740,745,748 };
        for (int rx : rxs) {
            SDL_SetRenderDrawColor(renderer, 80, 55, 20, 255);
            SDL_RenderLine(renderer, rx, (int)(WATER_Y + 5), rx, (int)(WATER_Y - 40));
            SDL_SetRenderDrawColor(renderer, 120, 80, 20, 255);
            SDL_FRect head = { (float)rx - 4,(float)(WATER_Y - 50),9,14 };SDL_RenderFillRect(renderer, &head);
        }
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

// ═══════════════════════════════════════════════════════════════════════════
//  HUD
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderHUD() {
    if (!player)return;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 15, 35, 170);
    SDL_FRect panel = { 8,8,220,78 };SDL_RenderFillRect(renderer, &panel);
    SDL_SetRenderDrawColor(renderer, 70, 150, 200, 200);SDL_RenderRect(renderer, &panel);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color yellow = { 255,230,60,255 }, white = { 210,235,255,255 };
    std::string sc = "ОЧКИ: " + std::to_string(player->getTotalScore());
    BF::draw(renderer, sc.c_str(), 16, 16, yellow, 2);
    std::string fc = "РЫБ:  " + std::to_string(player->getCatch().size());
    BF::draw(renderer, fc.c_str(), 16, 50, white, 2);

    // TAB подсказка
    SDL_Color dim = { 140,150,170,255 };
    BF::draw(renderer, "[TAB] Magaz.", WIN_W - 148, 12, dim, 2);

    renderStatusBar();
}

// ═══════════════════════════════════════════════════════════════════════════
//  Status bar (bottom)
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderStatusBar() {
    if (!player)return;
    BobberState bs = player->getBobberState();

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 15, 35, 185);
    SDL_FRect bar = { 0,(float)WIN_H - 46,(float)WIN_W,46 };SDL_RenderFillRect(renderer, &bar);
    SDL_SetRenderDrawColor(renderer, 50, 110, 170, 150);
    SDL_FRect border = { 0,(float)WIN_H - 46,(float)WIN_W,2 };SDL_RenderFillRect(renderer, &border);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color white = { 210,240,255,255 };
    SDL_Color yellow = { 255,230,50,255 };
    SDL_Color cyan = { 100,210,255,255 };
    SDL_Color red = { 255,70,70,255 };
    SDL_Color dim = { 140,155,175,255 };

    switch (bs) {
    case BobberState::IDLE:
    case BobberState::CAUGHT:
        BF::drawC(renderer, "[PROB./LKM] Zabros", WIN_W / 2, WIN_H - 34, white, 2);
        break;
    case BobberState::FLYING:
        BF::drawC(renderer, "Zabroska...", WIN_W / 2, WIN_H - 34, yellow, 2);
        break;
    case BobberState::FLOATING: {
        float prog = player->getBiteProgress();
        float bw = 310;float bx = (WIN_W - bw) * .5f;float by = WIN_H - 34;
        SDL_SetRenderDrawColor(renderer, 30, 40, 55, 255);
        SDL_FRect bg = { bx - 2,by - 2,bw + 4,14 };SDL_RenderFillRect(renderer, &bg);
        Uint8 cr = (Uint8)(40 + prog * 200), cg = (Uint8)(190 - prog * 130);
        SDL_SetRenderDrawColor(renderer, cr, cg, 40, 255);
        SDL_FRect fill = { bx,by,bw * prog,10 };SDL_RenderFillRect(renderer, &fill);
        SDL_Color wlbl = { 140,200,140,255 };
        BF::draw(renderer, "Zhdem...", WIN_W / 2 - 180, WIN_H - 34, wlbl, 2);
        break;
    }
    case BobberState::BITING:
        if (biteVisible) {
            BF::drawC(renderer, "!!! KLEV !!! [PROB./LKM]", WIN_W / 2, WIN_H - 36, red, 2);
        }
        break;
    case BobberState::REELING:
        renderTensionBar();
        BF::draw(renderer, "[PROB] = slab. natyaz.", WIN_W / 2 - 200, WIN_H - 20, cyan, 1);
        break;
    }

    BF::draw(renderer, "A/D - Lodka", WIN_W - 114, WIN_H - 34, dim, 2);

    // Леска оборвалась
    if (lineBreakTimer > 0) {
        SDL_Color lbr = { 255,80,80,255 };
        BF::drawC(renderer, "!LESCA OBORVALA'!", WIN_W / 2, (int)(WIN_H / 2 - 30), lbr, 3);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  Tension bar (мини-игра)
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderTensionBar() {
    if (!player)return;
    float t = player->getTension();
    float bw = 300;float bx = (WIN_W - bw) * .5f;float by = WIN_H - 38;

    // Фон
    SDL_SetRenderDrawColor(renderer, 25, 35, 50, 255);
    SDL_FRect bg = { bx - 2,by - 2,bw + 4,18 };SDL_RenderFillRect(renderer, &bg);

    // Зоны: зелёная (ok), жёлтая (осторожно), красная (обрыв)
    SDL_SetRenderDrawColor(renderer, 30, 160, 30, 255);
    SDL_FRect gz = { bx,by,bw * 0.6f,14 };SDL_RenderFillRect(renderer, &gz);
    SDL_SetRenderDrawColor(renderer, 200, 180, 0, 255);
    SDL_FRect yz = { bx + bw * 0.6f,by,bw * 0.25f,14 };SDL_RenderFillRect(renderer, &yz);
    SDL_SetRenderDrawColor(renderer, 180, 30, 30, 255);
    SDL_FRect rz = { bx + bw * 0.85f,by,bw * 0.15f,14 };SDL_RenderFillRect(renderer, &rz);

    // Индикатор натяжения
    Uint8 ir = (Uint8)(40 + t * 215), ig = (Uint8)(200 - t * 180);
    SDL_SetRenderDrawColor(renderer, ir, ig, 30, 255);
    float iw = 8;float ix = bx + t * (bw - iw);
    SDL_FRect ind = { ix,by - 2,iw,18 };SDL_RenderFillRect(renderer, &ind);

    // Метка
    SDL_Color tc = { 200,230,200,255 };
    BF::draw(renderer, "Natyaz.:", bx - 90, (int)by, tc, 2);
}

// ═══════════════════════════════════════════════════════════════════════════
//  Catch list
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderCatchList() {
    if (!player)return;
    const auto& catches = player->getCatch();
    if (catches.empty())return;
    int n = (int)catches.size();
    int show = n > 7 ? 7 : n;
    int start = n - show;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 15, 35, 165);
    SDL_FRect panel = { (float)WIN_W - 205.0f,8,197,(float)(22 + show * 15 + 6) };
    SDL_RenderFillRect(renderer, &panel);
    SDL_SetRenderDrawColor(renderer, 70, 150, 200, 180);SDL_RenderRect(renderer, &panel);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color hdr = { 255,200,70,255 }, ent = { 170,225,175,255 };
    BF::draw(renderer, "ULOV:", WIN_W - 198, 13, hdr, 1);
    int y = 26;
    for (int i = start;i < n;++i) {
        BF::draw(renderer, catches[i].c_str(), WIN_W - 198, y, ent, 1);
        y += 15;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  Catch popup
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderCatchPopup(float) {
    if (catchAnim <= 0 || catchMsg.empty())return;
    float alpha = SDL_min(catchAnim, 1.0f);
    float yoff = (catchAnim > 3.5f) ? (4.0f - catchAnim) * 60 : 0; // появление снизу

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 30, 10, (Uint8)(160 * alpha));
    SDL_FRect bg = { (float)WIN_W / 2 - 200,(float)WIN_H / 2 - 60 + yoff,400,80 };
    SDL_RenderFillRect(renderer, &bg);
    SDL_SetRenderDrawColor(renderer, 60, 200, 80, (Uint8)(200 * alpha));
    SDL_RenderRect(renderer, &bg);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color gc = { 80,255,100,255 };
    BF::drawC(renderer, "POYMANA!", WIN_W / 2, (int)(WIN_H / 2 - 50 + yoff), gc, 2);
    SDL_Color wc = { 220,255,220,255 };
    BF::drawC(renderer, catchMsg.c_str(), WIN_W / 2, (int)(WIN_H / 2 - 28 + yoff), wc, 2);
}

// ═══════════════════════════════════════════════════════════════════════════
//  Shop
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::renderShop() {
    // Полупрозрачный оверлей
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 10, 25, 220);
    SDL_FRect overlay = { 0,0,(float)WIN_W,(float)WIN_H };SDL_RenderFillRect(renderer, &overlay);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Color title = { 255,220,60,255 }, white = { 210,240,255,255 };
    SDL_Color green = { 80,220,100,255 }, gray = { 140,155,175,255 };

    BF::drawC(renderer, "=== MAGAZIN ===", WIN_W / 2, 20, title, 3);

    int score = player ? player->getTotalScore() : 0;
    std::string sc_s = "OCKI: " + std::to_string(score);
    BF::drawC(renderer, sc_s.c_str(), WIN_W / 2, 60, white, 2);

    auto btn = [&](int x, int y, int w, int h, const char* label, int cost, bool owned) {
        SDL_Color bc = owned ? SDL_Color{ 40,160,40,255 } : SDL_Color{ 30,50,80,255 };
        SDL_SetRenderDrawColor(renderer, bc.r, bc.g, bc.b, 255);
        SDL_FRect b = { (float)x,(float)y,(float)w,(float)h };SDL_RenderFillRect(renderer, &b);
        SDL_SetRenderDrawColor(renderer, owned ? 90 : 60, owned ? 200 : 120, owned ? 90 : 180, 255);
        SDL_RenderRect(renderer, &b);
        SDL_Color lc = owned ? green : white;
        BF::drawC(renderer, label, x + w / 2, y + 6, lc, 1);
        if (!owned) {
            std::string cs = std::to_string(cost) + " ok.";
            SDL_Color cc = (score >= cost) ? SDL_Color{ 100,255,100,255 } : SDL_Color{ 255,100,100,255 };
            BF::drawC(renderer, cs.c_str(), x + w / 2, y + 20, cc, 1);
        }
        else {
            BF::drawC(renderer, "VASH", x + w / 2, y + 20, green, 1);
        }
        };

    // ─── Лодки ───────────────────────────────────────────────────────────
    BF::draw(renderer, "LODKI:", 60, 130, title, 2);
    int bs = player ? (int)player->boatSkin : 0;
    btn(60, 155, 110, 50, "Derev.(bsp.)", 0, bs == 0);
    btn(180, 155, 110, 50, "Metal.(300)", 300, bs == 1);
    btn(300, 155, 110, 50, "Luxury(800)", 800, bs == 2);

    // ─── Удочки ──────────────────────────────────────────────────────────
    BF::draw(renderer, "UDOCHKI:", 60, 230, title, 2);
    int rs = player ? (int)player->rodSkin : 0;
    btn(60, 255, 110, 50, "Obych.(bsp.)", 0, rs == 0);
    btn(180, 255, 110, 50, "Carbon(200)", 200, rs == 1);
    btn(300, 255, 110, 50, "Zolot.(600)", 600, rs == 2);

    // ─── Локации ─────────────────────────────────────────────────────────
    BF::draw(renderer, "LOKACII:", 60, 330, title, 2);
    int lo = player ? player->location : 0;
    btn(60, 355, 110, 50, "Reka(bsp.)", 0, lo == 0);
    btn(180, 355, 110, 50, "Ozero(400)", 400, lo == 1);
    btn(300, 355, 110, 50, "More(1000)", 1000, lo == 2);

    BF::drawC(renderer, "[TAB/ESC] - zakryt magaz.", WIN_W / 2, WIN_H - 40, gray, 2);
}

// ═══════════════════════════════════════════════════════════════════════════
//  Render
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::render() {
    SDL_SetRenderDrawColor(renderer, 10, 35, 70, 255);
    SDL_RenderClear(renderer);

    if (gameState == GameState::PLAYING) {
        renderBg();
        if (player) player->render(renderer);
        renderHUD();
        renderCatchList();
        renderCatchPopup(0);
    }
    else {
        renderBg();
        if (player) player->render(renderer);
        renderShop();
    }

    SDL_RenderPresent(renderer);
}

// ═══════════════════════════════════════════════════════════════════════════
//  Clean
// ═══════════════════════════════════════════════════════════════════════════
void CalmWaters::clean() {
    if (player) { delete player;player = nullptr; }
    if (audioStream) { SDL_DestroyAudioStream(audioStream);audioStream = nullptr; }
    if (renderer) { SDL_DestroyRenderer(renderer);renderer = nullptr; }
    if (window) { SDL_DestroyWindow(window);window = nullptr; }
    SDL_Quit();
    std::cout << "Game closed.\n";
}

// ═══════════════════════════════════════════════════════════════════════════
//  main
// ═══════════════════════════════════════════════════════════════════════════
int main(int argc, char* argv[]) {
    CalmWaters game;
    if (game.init("Tikhie Vody - Rybalka", 800, 600)) {
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