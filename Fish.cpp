#include "Fish.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

Fish Fish::random() {
    Fish f;
    int r = rand() % 100;
    if (r < 35) {
        f.type = FishType::PERCH; f.name = "Okun";
        f.weight = 0.2f + (rand() % 15) / 10.0f;
        f.biteDelay = 2.0f + (rand() % 10) * 0.2f;
        f.rarity = 1;
    }
    else if (r < 60) {
        f.type = FishType::CRUCIAN; f.name = "Karas";
        f.weight = 0.3f + (rand() % 20) / 10.0f;
        f.biteDelay = 3.0f + (rand() % 8) * 0.3f;
        f.rarity = 1;
    }
    else if (r < 78) {
        f.type = FishType::CARP; f.name = "Karp";
        f.weight = 1.5f + (rand() % 40) / 10.0f;
        f.biteDelay = 4.0f + (rand() % 10) * 0.3f;
        f.rarity = 2;
    }
    else if (r < 90) {
        f.type = FishType::BREAM; f.name = "Leshch";
        f.weight = 0.8f + (rand() % 25) / 10.0f;
        f.biteDelay = 3.5f + (rand() % 8) * 0.3f;
        f.rarity = 2;
    }
    else if (r < 98) {
        f.type = FishType::PIKE; f.name = "Shchuka";
        f.weight = 3.0f + (rand() % 60) / 10.0f;
        f.biteDelay = 6.0f + (rand() % 10) * 0.4f;
        f.rarity = 3;
    }
    else {
        f.type = FishType::CATFISH; f.name = "Som";
        f.weight = 8.0f + (rand() % 120) / 10.0f;
        f.biteDelay = 9.0f + (rand() % 10) * 0.5f;
        f.rarity = 3;
    }
    return f;
}

std::string Fish::toString() const {
    std::ostringstream oss;
    oss << name << " " << std::fixed << std::setprecision(1) << weight << " kg";
    return oss.str();
}

int Fish::getScore() const {
    float mult = 1.0f;
    switch (type) {
    case FishType::CATFISH: mult = 5.0f; break;
    case FishType::PIKE:    mult = 3.0f; break;
    case FishType::CARP:    mult = 2.0f; break;
    case FishType::BREAM:   mult = 1.5f; break;
    case FishType::CRUCIAN: mult = 1.2f; break;
    case FishType::PERCH:   mult = 1.0f; break;
    }
    return static_cast<int>(weight * mult * 10);
}