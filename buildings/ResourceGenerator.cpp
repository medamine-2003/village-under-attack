#include "ResourceGenerator.h"

ResourceGenerator::ResourceGenerator(int x, int y, const std::string& r, int sx, int sy, int c, int max)
    : Building(x, y, r, sx, sy, c, max), current(0) {}

bool ResourceGenerator::isFull() const {
    return current >= capacity;
}

void ResourceGenerator::update() {
    if (!isFull()) {
        current++;
    }
}
