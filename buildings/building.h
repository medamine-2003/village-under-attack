#ifndef BUILDING_H
#define BUILDING_H
#include "../Position.h"
#include "../Resources.h"
#include <string>

class Building {
protected:
    int sizeX;
    int sizeY;
    std::string repr;
    int costGold;
    int costElixir;
    int maxInstances;
    Position position;
    int health;

public:
    Building(int sizeX, int sizeY, std::string repr, int costGold, int costElixir, int maxInstances, Position pos, int health);
    virtual ~Building() = default;

    // Getters
    int getSizeX() const;
    int getSizeY() const;
    std::string getRepr() const;
    Position getPosition() const;
    int getHealth() const;

    // Methods
    virtual bool canPlace(const Resources& resources) const;
    virtual void takeDamage(int damage);
};

#endif
