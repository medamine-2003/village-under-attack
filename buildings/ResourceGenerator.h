#pragma once
#include "building.h"

class ResourceGenerator : public Building {
protected:
    int current;
    const int capacity = 100;

public:
    ResourceGenerator(int x, int y, const std::string& r, int sx, int sy, int c, int max);

    bool isFull() const;
    virtual int collect() = 0;
    void update() override;
};
