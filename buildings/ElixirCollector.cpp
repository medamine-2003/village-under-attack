#include "ElixirCollector.h"

ElixirCollector::ElixirCollector(int x, int y) 
    : ResourceGenerator(x, y, "🧪", 3, 3, 100, 3) {}

int ElixirCollector::collect() {
    int collected = current;
    current = 0;
    return collected;
}
