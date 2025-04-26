#pragma once

class Resources {
    int gold;
    int elixir;

public:
    Resources(int g = 0, int e = 0);

    bool canAfford(int g, int e) const;
    void add(int g, int e);
    void spend(int g, int e);

    int getGold() const;
    int getElixir() const;
};
