#pragma once
#include <string>

enum class FishType { CARP, PERCH, PIKE, BREAM, CRUCIAN, CATFISH };

struct Fish {
    FishType    type = FishType::CARP;
    float       weight = 0.0f;
    float       biteDelay = 0.0f;
    std::string name;
    int         rarity = 1; // 1=обычная 2=редкая 3=легендарная

    static Fish random();
    std::string toString() const;
    int getScore() const;
};