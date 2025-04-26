#include "Resources.h"

Resources::Resources(int g, int e) : gold(g), elixir(e) {}

bool Resources::canAfford(int g, int e) const {
    return gold >= g && elixir >= e;
}

void Resources::add(int g, int e) {
    gold += g;
    elixir += e;
}

void Resources::spend(int g, int e) {
    gold -= g;
    elixir -= e;
}

int Resources::getGold() const { return gold; }
int Resources::getElixir() const { return elixir; }
