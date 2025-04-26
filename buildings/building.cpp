
#include "building.h"

Building::Building(int x, int y, const std::string& r, int sx, int sy, int c, int max)
    : position(x, y), sizeX(sx), sizeY(sy), repr(r), cost(c), maxInstances(max), health(100) {}

bool Building::isColliding(const Position& pos) const {
    int left = position.x - sizeX/2;
    int right = position.x + sizeX/2;
    int top = position.y - sizeY/2;
    int bottom = position.y + sizeY/2;

    return (pos.x >= left && pos.x <= right && 
            pos.y >= top && pos.y <= bottom);
}

void Building::takeDamage(int amount) {
    health -= amount;
}

bool Building::isDestroyed() const {
    return health <= 0;
}

// Getters implementation
Position Building::getPosition() const { return position; }
int Building::getSizeX() const { return sizeX; }
int Building::getSizeY() const { return sizeY; }
std::string Building::getRepr() const { return repr; }
int Building::getCost() const { return cost; }
int Building::getMaxInstances() const { return maxInstances; }
int Building::getHealth() const { return health; }
