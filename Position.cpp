#include "Position.h"
#include <cmath>

float Position::distanceTo(const Position& other) const {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Position Position::operator-(const Position& other) const {
    return Position(x - other.x, y - other.y);
}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}
