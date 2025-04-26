#include "GoldMine.h"

GoldMine::GoldMine(int x, int y) 
    : ResourceGenerator(x, y, "⛏️", 3, 3, 100, 3) {}

int GoldMine::collect() {
    int collected = current;
    current = 0;
    return collected;
}
