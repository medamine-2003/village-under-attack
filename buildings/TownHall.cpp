#include "TownHall.h"

TownHall::TownHall(int x, int y) 
    : Building(x, y, "✅️", 5, 5, 0, 1) {
    health = 200; // TownHall has more health
}

void TownHall::update() {
    // TownHall doesn't need regular updates
}
