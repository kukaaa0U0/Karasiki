#include "CalmWaters.h"

CalmWaters::CalmWaters() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
    player = nullptr;
}

CalmWaters::~CalmWaters() {
    clean();
}

bool CalmWaters::init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL не смог запуститься! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        std::cerr << "Не удалось создать окно! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Не удалось создать рендерер! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;

    player = new Player();
    player->init(350.0f, 400.0f, 100.0f, 50.0f);

    return true;
}

void CalmWaters::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
    inputHandler.update(); // обновляем состояние клавиатуры здесь
}

void CalmWaters::update() {
    if (player) {
        player->update(inputHandler); // передаём inputHandler в игрока
    }
}

void CalmWaters::render() {
    SDL_SetRenderDrawColor(renderer, 30, 90, 140, 255);
    SDL_RenderClear(renderer);

    if (player) {
        player->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void CalmWaters::clean() {
    if (player) {
        delete player;
        player = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr; // обнуляем, чтобы не было двойного удаления
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr; // обнуляем, чтобы не было двойного удаления
    }
    SDL_Quit();
    std::cout << "Игра успешно закрыта, память очищена!" << std::endl;
}

int main(int argc, char* argv[]) {
    CalmWaters* game = new CalmWaters();

    if (game->init("Calm Waters - Наша Рыбалка", 800, 600)) {
        while (game->running()) {
            game->handleEvents();
            game->update();
            game->render();
            SDL_Delay(16);
        }
    }

    game->clean();
    delete game;

    return 0;
}