#include "Board.h"
#include "buildings/TownHall.h"
#include "Entities/Enemies/Raider.h"
#include <algorithm>
#include <random>

Board::Board(int w, int h) 
    : player(w/2, h/2), width(w), height(h) {
    // Add initial TownHall
    buildings.push_back(std::make_unique<TownHall>(width/2, height/2));
    lastEnemySpawn = std::chrono::system_clock::now();
}

void Board::update() {
    // Update all buildings
    for (auto& building : buildings) {
        building->update();
    }

    // Update all enemies
    for (auto& enemy : enemies) {
        enemy->update();
    }

    // Spawn enemies periodically
    auto now = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - lastEnemySpawn).count() > 30) {
        spawnEnemy();
        lastEnemySpawn = now;
    }

    // Remove destroyed buildings
    buildings.erase(
        std::remove_if(buildings.begin(), buildings.end(),
            [](const std::unique_ptr<Building>& b) { return b->isDestroyed(); }),
        buildings.end());

    // Remove destroyed enemies
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) { return e->isDestroyed(); }),
        enemies.end());
}

bool Board::addBuilding(std::unique_ptr<Building> building) {
    // Check if position is available
    for (const auto& existing : buildings) {
        if (existing->isColliding(building->getPosition())) {
            return false;
        }
    }

    buildings.push_back(std::move(building));
    return true;
}

Building* Board::getBuildingAt(const Position& pos) const {
    for (const auto& building : buildings) {
        if (building->isColliding(pos)) {
            return building.get();
        }
    }
    return nullptr;
}

void Board::spawnEnemy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, width-1);

    int x = dist(gen);
    int y = (dist(gen) % 2 == 0) ? 0 : height-1;

    auto enemy = std::make_unique<Raider>(x, y);
    std::vector<Building*> buildingPtrs;
    for (const auto& b : buildings) {
        buildingPtrs.push_back(b.get());
    }
    enemy->findTarget(buildingPtrs);
    enemies.push_back(std::move(enemy));
}

Player& Board::getPlayer() const { return const_cast<Player&>(player); }
const std::vector<std::unique_ptr<Building>>& Board::getBuildings() const { return buildings; }
const std::vector<std::unique_ptr<Enemy>>& Board::getEnemies() const { return enemies; }

bool Board::isTownHallDestroyed() const {
    for (const auto& building : buildings) {
        if (dynamic_cast<TownHall*>(building.get())) {
            return building->isDestroyed();
        }
    }
    return true;
}
