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
    // 1. Инициализируем графический движок SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL не смог запуститься! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    // 2. Создаем окно
    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        std::cerr << "Не удалось создать окно! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    // 3. Создаем рендерер (nullptr — автовыбор видеокарты)
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Не удалось создать рендерер! Ошибка: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;

    // 4. Выделяем память под игрока и задаем его стартовую позицию
    player = new Player();
    // Размещаем коричневый прямоугольник (лодку) по центру экрана, ближе к низу
    player->init(350.0f, 400.0f, 100.0f, 50.0f);

    return true;
}

void CalmWaters::handleEvents() {
    SDL_Event event;
    // Проверяем, не нажал ли пользователь на крестик окна
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
}

void CalmWaters::update() {
    // Каждый кадр обновляем логику игрока (пока она пустая)
    if (player) {
        player->update();
    }
}

void CalmWaters::render() {
    // Красим фон в красивый цвет спокойной глубокой воды (RGB: 30, 90, 140)
    SDL_SetRenderDrawColor(renderer, 30, 90, 140, 255);
    SDL_RenderClear(renderer); // Заливаем экран этим цветом

    // Рисуем нашего игрока поверх воды
    if (player) {
        player->render(renderer);
    }

    // Выводим всё, что нарисовали, на экран
    SDL_RenderPresent(renderer);
}

void CalmWaters::clean() {
    // Чистим память в обратном порядке
    if (player) {
        delete player;
        player = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    std::cout << "Игра успешно закрыта, память очищена!" << std::endl;
}

// Точка входа в программу. CMake зацепится за этот main
int main(int argc, char* argv[]) {
    CalmWaters* game = new CalmWaters();

    // Запускаем окно 800х600
    if (game->init("Calm Waters - Наша Рыбалка", 800, 600)) {

        // Главный игровой цикл
        while (game->running()) {
            game->handleEvents(); // Проверили клики/закрытие
            game->update();       // Посчитали физику/логику
            game->render();       // Нарисовали картинку

            SDL_Delay(16);        // Ограничиваем FPS примерно до 60 кадров
        }
    }

    game->clean();
    delete game;

    return 0;
}