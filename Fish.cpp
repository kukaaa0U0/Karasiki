#include "Fish.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

Fish Fish::random() {
    Fish f;
    int r = rand() % 4;
    switch (r) {
    case 0: f.type = FishType::CARP;  f.name = "Karp";  f.weight = 1.5f + (rand() % 30) / 10.0f; f.biteDelay = 4.0f; break;
    case 1: f.type = FishType::PERCH; f.name = "Okun";  f.weight = 0.2f + (rand() % 10) / 10.0f; f.biteDelay = 2.0f; break;
    case 2: f.type = FishType::PIKE;  f.name = "Shchuka"; f.weight = 3.0f + (rand() % 50) / 10.0f; f.biteDelay = 7.0f; break;
    case 3: f.type = FishType::BREAM; f.name = "Leshch"; f.weight = 0.8f + (rand() % 20) / 10.0f; f.biteDelay = 3.5f; break;
    }
    return f;
}

std::string Fish::toString() const {
    std::ostringstream oss;
    oss << name << " " << std::fixed << std::setprecision(1) << weight << " kg";
    return oss.str();
}

int Fish::getScore() const {
    // очки = вес * множитель по типу
    float mult = 1.0f;
    switch (type) {
    case FishType::PIKE:  mult = 3.0f; break;
    case FishType::CARP:  mult = 2.0f; break;
    case FishType::BREAM: mult = 1.5f; break;
    case FishType::PERCH: mult = 1.0f; break;
    }
    return static_cast<int>(weight * mult * 10);
}