#pragma once
#include "ResourceGenerator.h"

class GoldMine : public ResourceGenerator {
public:
    GoldMine(int x, int y);
    int collect() override;
};
