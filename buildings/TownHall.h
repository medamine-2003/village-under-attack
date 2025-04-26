#pragma once
#include "building.h"

class TownHall : public Building {
public:
    TownHall(int x, int y);
    void update() override;
};
