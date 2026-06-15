/**
 * @file InputHandler.h
 * @brief Обработчик пользовательского ввода (клавиатура и мышь)
 * @author Разработчик игры
 * @version 1.0
 * @date 2024
 *
 * Этот модуль предоставляет класс InputHandler для получения информации
 * о нажатых клавишах и движениях мыши в текущем кадре.
 */

#pragma once

#include <SDL3/SDL.h>

 /**
  * @class InputHandler
  * @brief Класс для обработки пользовательского ввода
  *
  * InputHandler инкапсулирует логику получения информации о состоянии
  * клавиатуры и мыши. Используется игровым циклом для проверки действий игрока.
  *
  * @note Метод update() должен вызываться один раз за кадр перед использованием
  *       методов проверки состояния клавиш.
  */
class InputHandler {
public:
    /**
     * @brief Обновляет состояние всех кнопок клавиатуры
     *
     * Это должно быть вызвано один раз в начале цикла обработки события.
     * После вызова все методы проверки состояния (isKeyDown) будут работать
     * с актуальной информацией.
     *
     * @note Внутри функции вызывается SDL_GetKeyboardState()
     *
     * @example
     * @code
     * inputHandler.update();
     * if (inputHandler.isKeyDown(SDL_SCANCODE_SPACE)) {
     *     // обработка нажатия пробела
     * }
     * @endcode
     */
    void update();

    /**
     * @brief Проверяет, нажата ли конкретная клавиша в текущем кадре
     *
     * @param key Сканкод клавиши (SDL_SCANCODE_*)
     * @return true если клавиша нажата, false если отпущена
     *
     * @note Эта функция просто проверяет состояние - не различает
     *       нажатие и удержание. Для обнаружения одного нажатия
     *       необходимо отслеживать изменение состояния между кадрами.
     *
     * @example
     * @code
     * // Основные клавиши для управления лодкой:
     * if (inputHandler.isKeyDown(SDL_SCANCODE_A)) { /* влево */

///    \n*if (inputHandler.isKeyDown(SDL_SCANCODE_D)) { /* вправо */ }
///    \n*if (inputHandler.isKeyDown(SDL_SCANCODE_LEFT)) { /* влево */ }
///    \n*if (inputHandler.isKeyDown(SDL_SCANCODE_RIGHT)) { /* вправо */ }
///    \n*
///    \n* // Управление рыбалкой:
///    \n*if (inputHandler.isKeyDown(SDL_SCANCODE_SPACE)) { /* заброс/вытягивание */ }
///    \n*if (inputHandler.isKeyDown(SDL_SCANCODE_TAB)) { /* магазин */ }
///    \n*@endcode
///    \n*
///    \n*/
bool isKeyDown(SDL_Scancode key) const;

private:
    /// @brief Указатель на массив состояния клавиатуры из SDL
    const bool* keyboardState = nullptr;
};