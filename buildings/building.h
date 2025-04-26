#pragma once
#include "../Position.h"
#include <string>
#include <memory>

class Building {
protected:
    Position position;
    int sizeX;
    int sizeY;
    std::string repr;
    int cost;
    int maxInstances;
    int health;

public:
    Building(int x, int y, const std::string& r, int sx, int sy, int c, int max);
    virtual ~Building() = default;

    bool isColliding(const Position& pos) const;
    virtual void update() = 0;
    void takeDamage(int amount);
    bool isDestroyed() const;

    Position getPosition() const;
    int getSizeX() const;
    int getSizeY() const;
    std::string getRepr() const;
    int getCost() const;
    int getMaxInstances() const;
    int getHealth() const;
};
