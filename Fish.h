#pragma once
#include <string>

enum class FishType {
    CARP,    //  арп    Ч медленный клЄв, т€жЄлый
    PERCH,   // ќкунь   Ч быстрый клЄв, лЄгкий
    PIKE,    // ўука    Ч редкий, но большой
    BREAM    // Ћещ     Ч средний
};

struct Fish {
    FishType type = FishType::CARP;
    float weight = 0.0f;     // кг
    float biteDelay = 0.0f;  // через сколько секунд клюнет
    std::string name;

    static Fish random();
    std::string toString() const;
    int getScore() const;    // очки за рыбу
};