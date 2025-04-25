#pragma once

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    float distanceTo(const Position& other) const;
    bool operator==(const Position& other) const;
    Position operator-(const Position& other) const;
};
