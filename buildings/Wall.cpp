#include "Wall.h"

Wall::Wall(int x, int y) 
    : Building(x, y, "🧱", 1, 1, 10, 200) {}

void Wall::update() {
    // Wall doesn't need regular updates
}
