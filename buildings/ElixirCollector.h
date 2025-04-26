#pragma once
#include "ResourceGenerator.h"

class ElixirCollector : public ResourceGenerator {
public:
    ElixirCollector(int x, int y);
    int collect() override;
};
