#include "Fish.h"
#include <cstdlib>

Fish Fish::random() {
    Fish f;
    int r = rand() % 4;
    switch (r) {
    case 0: f.type = FishType::CARP;  f.name = "Карп";  f.weight = 1.5f + (rand() % 30) / 10.0f; f.biteDelay = 4.0f; break;
    case 1: f.type = FishType::PERCH; f.name = "Окунь"; f.weight = 0.2f + (rand() % 10) / 10.0f; f.biteDelay = 2.0f; break;
    case 2: f.type = FishType::PIKE;  f.name = "Щука";  f.weight = 3.0f + (rand() % 50) / 10.0f; f.biteDelay = 7.0f; break;
    case 3: f.type = FishType::BREAM; f.name = "Лещ";   f.weight = 0.8f + (rand() % 20) / 10.0f; f.biteDelay = 3.5f; break;
    }
    return f;
}

std::string Fish::toString() const {
    return name + " " + std::to_string(weight).substr(0, 4) + " кг";
}