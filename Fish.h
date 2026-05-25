#pragma once
#include <string>

enum class FishType {
    CARP,    //  арп    Ч медленный клЄв, т€жЄлый
    PERCH,   // ќкунь   Ч быстрый клЄв, лЄгкий
    PIKE,    // ўука    Ч редкий, но большой
    BREAM    // Ћещ     Ч средний
};

struct Fish {
    FishType type;
    float weight;        // кг
    float biteDelay;     // через сколько секунд клюнет
    std::string name;

    // √енерирует случайную рыбу
    static Fish random();
    std::string toString() const;
};