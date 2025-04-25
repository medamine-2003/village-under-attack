#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include "Position.h"
#include "buildings/building.h"
#include "Entities/Player.h"
#include "Entities/Enemies/Enemy.h"

class Board {
    std::vector<std::unique_ptr<Building>> buildings;
    std::vector<std::unique_ptr<Enemy>> enemies;
    Player player;
    int width;
    int height;
    std::chrono::time_point<std::chrono::system_clock> lastEnemySpawn;

public:
    Board(int w, int h);

    void update();
    bool addBuilding(std::unique_ptr<Building> building);
    Building* getBuildingAt(const Position& pos) const;
    void spawnEnemy();

    Player& getPlayer() const;
    const std::vector<std::unique_ptr<Building>>& getBuildings() const;
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const;
    bool isTownHallDestroyed() const;
};
