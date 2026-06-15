/**
 * @file Player.h
 * @brief Класс игрока, управления лодкой и удочкой
 * @author Ищенко Кирилл
 * @version 1.0
 * @date 2026
 *
 * Этот модуль содержит класс Player, который представляет рыбака на лодке.
 * Управляет движением лодки, удочкой, сбором улова и скинами.
 */

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "InputHandler.h"
#include "FishingRod.h"

 /**
  * @enum PlayerState
  * @brief Состояния рыбака в игре
  */
enum class PlayerState {
    IDLE,      ///< В покое, ничего не происходит
    CASTING,   ///< Выполняется заброс
    WAITING,   ///< Ждём клева или поплавок плывёт
    REELING    ///< Вытягиваем рыбу (мини-игра натяжения)
};

/**
 * @enum BoatSkin
 * @brief Доступные скины лодки
 *
 * Скины улучшают внешний вид, но не влияют на игровой процесс.
 * Можно купить в магазине за очки.
 */
enum class BoatSkin {
    WOOD = 0,      ///< Деревянная лодка (начальный)
    METAL = 1,     ///< Металлическая лодка (300 очков)
    LUXURY = 2     ///< Люксовая лодка (800 очков)
};

/**
 * @enum RodSkin
 * @brief Доступные скины удочки
 *
 * Скины улучшают внешний вид, но не влияют на игровой процесс.
 * Можно купить в магазине за очки.
 */
enum class RodSkin {
    BASIC = 0,     ///< Обычная удочка (начальная)
    CARBON = 1,    ///< Карбоновая удочка (200 очков)
    GOLDEN = 2     ///< Золотая удочка (600 очков)
};

/**
 * @struct ShopItem
 * @brief Структура предмета магазина
 */
struct ShopItem {
    /// @brief Название предмета
    std::string name;

    /// @brief Стоимость в очках
    int cost;

    /// @brief Разблокирован ли этот предмет
    bool unlocked = false;
};

/**
 * @class Player
 * @brief Класс игрока (рыбака на лодке)
 *
 * Player управляет:
 * - Движением лодки влево/вправо
 * - Удочкой и процессом рыбалки
 * - Сбором и подсчётом улова
 * - Покупкой скинов и локаций
 * - Отрисовкой рыбака и лодки
 *
 * @note Игрок имеет фиксированный Y (на воде), может двигаться только по X
 */
class Player {
public:
    /**
     * @brief Конструктор
     *
     * Инициализирует начальные значения игрока.
     */
    Player();

    /**
     * @brief Деструктор
     *
     * Очищает ресурсы и выводит статистику.
     */
    ~Player();

    /**
     * @brief Инициализирует игрока
     *
     * Устанавливает начальное положение лодки и инициализирует удочку.
     *
     * @param x X-координата начального положения лодки
     * @param y Y-координата начального положения лодки
     * @param width Ширина лодки в пикселях
     * @param height Высота лодки в пикселях
     *
     * @example
     * @code
     * player.init(350.0f, 385.0f, 100.0f, 45.0f);
     * @endcode
     */
    void init(float x, float y, float width, float height);

    /**
     * @brief Обновляет логику игрока каждый кадр
     *
     * Обновляет:
     * - Движение лодки в зависимости от ввода
     * - Удочку и поплавок
     * - Проверку поймённых рыб
     * - Состояние игрока
     *
     * @param dt Дельта времени в секундах
     * @param input Обработчик ввода
     * @param mouseX X-координата мыши
     * @param mouseY Y-координата мыши
     * @param mouseClicked true если нажата ЛКМ
     *
     * @note Должно быть вызвано один раз за кадр
     */
    void update(float dt, const InputHandler& input,
        float mouseX, float mouseY, bool mouseClicked);

    /**
     * @brief Отрисовывает игрока, лодку и удочку
     *
     * Рисует:
     * - Тень лодки
     * - Корпус лодки (цвет зависит от скина)
     * - Сиденье в лодке
     * - Рыбака (тело, голова, шляпа)
     * - Удочку и поплавок
     *
     * @param renderer SDL рендерер
     */
    void render(SDL_Renderer* renderer);

    /**
     * @brief Очищает ресурсы игрока
     *
     * Выводит финальную статистику в консоль.
     */
    void clean();

    // ?????????????????????????????????????????????????????????????????????
    //   GETTERS
    // ?????????????????????????????????????????????????????????????????????

    /**
     * @brief Получает текущее состояние игрока
     *
     * @return Текущее состояние (PlayerState)
     */
    PlayerState getState() const { return currentState; }

    /**
     * @brief Получает список пойманных рыб
     *
     * @return Const ссылка на вектор с описаниями рыб
     */
    const std::vector<std::string>& getCatch() const { return caughtFish; }

    /**
     * @brief Получает общее количество накопленных очков
     *
     * @return Количество очков
     */
    int getTotalScore() const { return totalScore; }

    /**
     * @brief Получает состояние поплавка
     *
     * @return Текущее состояние (BobberState)
     */
    BobberState getBobberState() const { return rod.getBobberState(); }

    /**
     * @brief Получает прогресс ожидания клева
     *
     * @return Значение от 0 до 1
     */
    float getBiteProgress() const { return rod.getBiteProgress(); }

    /**
     * @brief Получает натяжение лески
     *
     * @return Значение от 0 до 1
     */
    float getTension() const { return rod.getTension(); }

    /**
     * @brief Проверяет, порвалась ли леса
     *
     * @return true если леса порвалась
     */
    bool hadLineBroken() const { return rod.hadLineBroken(); }

    /**
     * @brief Сбрасывает флаг разрыва лески
     */
    void clearLineBroke() { rod.clearLineBroke(); }

    /**
     * @brief Получает X-координату игрока
     *
     * @return X-позиция лодки
     */
    float getX() const { return destRect.x; }

    /**
     * @brief Получает Y-координату игрока
     *
     * @return Y-позиция лодки
     */
    float getY() const { return destRect.y; }

    // ?????????????????????????????????????????????????????????????????????
    //   SHOP & SKINS
    // ?????????????????????????????????????????????????????????????????????

    /// @brief Текущий скин лодки
    BoatSkin boatSkin = BoatSkin::WOOD;

    /// @brief Текущий скин удочки
    RodSkin rodSkin = RodSkin::BASIC;

    /// @brief Текущая локация (0=река, 1=озеро, 2=море)
    int location = 0;

    /**
     * @brief Покупает скин лодки
     *
     * @param idx Индекс скина (0=деревянная, 1=металл, 2=люкс)
     * @return true если покупка успешна, false если недостаточно очков
     *
     * @example
     * @code
     * if (player.buyBoat(1)) {
     *     std::cout << "Купил металлическую лодку!" << std::endl;
     * }
     * @endcode
     */
    bool buyBoat(int idx);

    /**
     * @brief Покупает скин удочки
     *
     * @param idx Индекс скина (0=обычная, 1=карбон, 2=золотая)
     * @return true если покупка успешна
     */
    bool buyRod(int idx);

    /**
     * @brief Покупает новую локацию для рыбалки
     *
     * @param idx Индекс локации (0=река, 1=озеро, 2=море)
     * @return true если покупка успешна
     */
    bool buyLocation(int idx);

    // ?????????????????????????????????????????????????????????????????????
    //   CATCH MANAGEMENT
    // ?????????????????????????????????????????????????????????????????????

    /// @brief Последняя поймённая рыба (для всплывающего уведомления)
    std::string lastCatch;

    /// @brief Флаг: поймана ли новая рыба в этом кадре
    bool newCatch = false;

private:
    /// @brief Прямоугольник лодки (позиция и размер)
    SDL_FRect destRect = { 0, 0, 0, 0 };

    /// @brief Текущее состояние рыбака
    PlayerState currentState = PlayerState::IDLE;

    /// @brief Удочка рыбака
    FishingRod rod;

    /// @brief Список всех пойманных рыб (строки формата "Название Вес")
    std::vector<std::string> caughtFish;

    /// @brief Общее количество накопленных очков
    int totalScore = 0;

    /// @brief Левая граница экрана (минимальная X лодки)
    static constexpr float WATER_LEFT = 20.0f;

    /// @brief Правая граница экрана (максимальная X лодки)
    static constexpr float WATER_RIGHT = 700.0f;

    /// @brief Скорость движения лодки в пикселях/сек
    static constexpr float MOVE_SPEED = 160.0f;
};