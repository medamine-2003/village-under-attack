#pragma once
#include "building.h"

class Wall : public Building {
public:
    Wall(int x, int y);
    void update() override;
};
