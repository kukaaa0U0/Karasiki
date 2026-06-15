/**
 * @file FishingRod.h
 * @brief Класс удочки и управления её состоянием
 * @author Разработчик игры
 * @version 1.0
 * @date 2024
 *
 * Этот модуль содержит класс FishingRod, который обрабатывает пользовательский
 * ввод для управления удочкой и координирует действия поплавка (Bobber).
 */

#pragma once

#include <SDL3/SDL.h>
#include "Boobber.h"
#include "InputHandler.h"

 /**
  * @class FishingRod
  * @brief Класс удочки, управляющий забросом и вытягиванием рыбы
  *
  * FishingRod инкапсулирует логику удочки и координирует работу с поплавком.
  * Он обрабатывает пользовательский ввод (нажатия пробела и клики мыши)
  * и передаёт соответствующие команды поплавку.
  *
  * Логика управления:
  * - PРОБЕЛ при IDLE: случайный заброс
  * - ПРОБЕЛ при FLOATING: упустил клев!
  * - ПРОБЕЛ при BITING: начать вытягивание
  * - ПРОБЕЛ при REELING: ослабить натяжение
  * - ЛКМ: заброс в точку мыши (вместо пробела)
  */
class FishingRod {
public:
    /**
     * @brief Инициализирует удочку
     *
     * Устанавливает положение удочки относительно лодки игрока.
     *
     * @param playerX X-координата игрока (лодки)
     * @param playerY Y-координата игрока
     *
     * @example
     * @code
     * rod.init(playerX, playerY);
     * @endcode
     */
    void init(float playerX, float playerY);

    /**
     * @brief Синхронизирует позицию удочки с позицией игрока
     *
     * Должно быть вызвано каждый кадр для отслеживания движения лодки.
     * Если поплавок в покое, также обновляет его домашнюю позицию.
     *
     * @param playerX X-координата игрока
     * @param playerY Y-координата игрока
     *
     * @note Это критичное для того чтобы удочка всегда была с лодкой
     */
    void syncPosition(float playerX, float playerY);

    /**
     * @brief Обновляет логику удочки каждый кадр
     *
     * Обрабатывает пользовательский ввод, обновляет поплавок и проверяет
     * наличие поймённой рыбы.
     *
     * @param dt Дельта времени в секундах
     * @param input Обработчик ввода
     * @param mouseX X-координата мыши (для забросов в точку)
     * @param mouseY Y-координата мыши
     * @param mouseClicked true если нажата левая кнопка мыши
     *
     * @note Должно быть вызвано один раз за кадр
     *
     * @example
     * @code
     * rod.update(dt, inputHandler, mouseX, mouseY, mouseClicked);
     * @endcode
     */
    void update(float dt, const InputHandler& input,
        float mouseX, float mouseY, bool mouseClicked);

    /**
     * @brief Отрисовывает удочку и поплавок на экран
     *
     * Рисует:
     * - Удилище (коричневая линия)
     * - Леску (от удилища до поплавка, цвет зависит от натяжения)
     * - Поплавок (делегирует отрисовку Bobber)
     *
     * @param renderer SDL рендерер
     *
     * @note Должно быть вызвано в функции render() Player
     */
    void render(SDL_Renderer* renderer);

    /**
     * @brief Проверяет, поймана ли рыба
     *
     * @return true если рыба успешно поймана и готова к сдаче
     *
     * @see collectFish()
     */
    bool hasCatch() const;

    /**
     * @brief Собирает поймённую рыбу
     *
     * Возвращает информацию о рыбе и сбрасывает состояние поплавка.
     * После этого вызова можно выполнять новый заброс.
     *
     * @return Структура Fish с информацией о поймённой рыбе
     *
     * @warning Используйте только после проверки hasCatch() == true
     *
     * @example
     * @code
     * if (rod.hasCatch()) {
     *     Fish fish = rod.collectFish();
     *     std::cout << "Поймал: " << fish.toString() << std::endl;
     * }
     * @endcode
     */
    Fish collectFish();

    /**
     * @brief Проверяет, порвалась ли леса
     *
     * @return true если леса порвалась из-за перенатяжения при вытягивании
     *
     * @see clearLineBroke()
     */
    bool hadLineBroken() const { return rodLineBroke; }

    /**
     * @brief Сбрасывает флаг разрыва лески
     *
     * Должно быть вызвано после обработки события разрыва лески
     * в главной программе.
     */
    void clearLineBroke() { rodLineBroke = false; }

    /**
     * @brief Получает текущее состояние поплавка
     *
     * @return Текущее состояние (BobberState)
     *
     * @see BobberState
     */
    BobberState getBobberState() const { return bobber.getState(); }

    /**
     * @brief Получает прогресс ожидания клева (0..1)
     *
     * @return Значение от 0 до 1 (0 = свежий заброс, 1.0 = пора клёв)
     *
     * @note Используется для отрисовки прогресс-бара в HUD
     */
    float getBiteProgress() const { return bobber.getBiteProgress(); }

    /**
     * @brief Получает натяжение лески при вытягивании (0..1)
     *
     * @return Текущее натяжение лески
     *
     * @note Используется для отрисовки шкалы натяжения в HUD
     */
    float getTension() const { return bobber.getTension(); }

    /// @brief X-координата конца удилища (откуда вылетает леска)
    float rodX = 0;

    /// @brief Y-координата конца удилища
    float rodY = 0;

private:
    /// @brief Поплавок, управляемый удочкой
    Bobber bobber;

    /// @brief Флаг: был ли пробел нажат в прошлом кадре
    bool spaceWasDown = false;

    /// @brief Флаг: была ли мышь нажата в прошлом кадре
    bool mouseWasClick = false;

    /// @brief Флаг: порвалась ли леса в этом сеансе рыбалки
    bool rodLineBroke = false;

    /**
     * @brief Обрабатывает пользовательский ввод
     *
     * Это внутренний метод, отвечающий за:
     * - Обнаружение нажатия пробела
     * - Проверку нажатия мыши
     * - Передачу команд поплавку в зависимости от его состояния
     *
     * @param input Обработчик ввода
     * @param mouseX X-координата мыши
     * @param mouseY Y-координата мыши
     * @param mouseClicked true если нажата ЛКМ
     */
    void handleInput(const InputHandler& input,
        float mouseX, float mouseY, bool mouseClicked);
};