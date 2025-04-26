#pragma once
#include "../Position.h"
#include <string>

class Entity {
protected:
    Position position;
    std::string repr;
    int health;

public:
    Entity(int x, int y, const std::string& r, int h);
    virtual ~Entity() = default;

    virtual void update() = 0;
    void takeDamage(int amount);
    bool isDestroyed() const;

    Position getPosition() const;
    std::string getRepr() const;
    int getHealth() const;
};
